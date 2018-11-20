// Fill out your copyright notice in the Description page of Project Settings.

#include "ImageSubscriber.h"

#include "SIMPLE_Common.h"

THIRD_PARTY_INCLUDES_START
#include <simple/client.hpp>
#include <simple_msgs/int.hpp>
THIRD_PARTY_INCLUDES_END

#include "Runtime/Core/Public/HAL/Runnable.h"
#include "Runtime/Core/Public/HAL/RunnableThread.h"

AImageSubscriber::AImageSubscriber()
  : AActor()
  , Port{0}
  , Url{TEXT("")}
  , isActive{false}
  , ImageSize{0, 0, 0}
  , VideoTexture{nullptr}
  , Subscriber{nullptr} {
  PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AImageSubscriber::BeginPlay() {
  Super::BeginPlay();
  // try to connect - if parameters are unset, nothing will happen
  Connect();
}

void AImageSubscriber::EndPlay(const EEndPlayReason::Type EndPlayReason) {
  Stop();
  Super::EndPlay(EndPlayReason);
}

void AImageSubscriber::Tick(float DeltaTime) {
  if (HasReceivedImage) {
    FScopeLock lock(&SwapMutex);
    if (UploadTexture) {
      VideoTexture = ReceivedImage->toRenderTarget(VideoTexture, false);
    }
    HasReceivedImage = false;
    OnFrameReceived();
  }
}

void AImageSubscriber::ConnectTo(FString Url, int32 Port) {
  this->Url = Url;
  this->Port = Port;
  Connect();
}

void AImageSubscriber::Connect() {
  // Minor sanity check for the parameters
  if (Url.IsEmpty() || !Port) return;

  std::string url{TCHAR_TO_UTF8(*Url)};
  std::string address{url + ":" + std::to_string(Port)};
  try {
    Subscriber = std::make_unique<simple::Subscriber<simple_msgs::Image<uint8_t>>>(
        address, [&](const simple_msgs::Image<uint8_t>& img) { ProcessImage(img); });
    isActive = true;
  } catch (std::exception& e) {
    UE_LOG(SIMPLE, Warning, TEXT("Unable to connect: %s"), e.what());
  }
}

void AImageSubscriber::Stop() {
  Subscriber.reset();

  isActive = false;
}

void AImageSubscriber::ProcessImage(const simple_msgs::Image<uint8_t>& imgMsg) {
  auto& header = imgMsg.getHeader();
  auto* imageData = imgMsg.getImageData();
  auto imageSize = imgMsg.getImageDimensions();

  if (!ReceivedBackBuffer) {
    ReceivedBackBuffer = NewObject<UCVUMat>();
  }

  cv::Mat wrap;
  if (imageSize[2] == 1) {
    // 2D images
    // Wrap in a cv::Mat and copy the buffer
    wrap = cv::Mat{static_cast<int>(imageSize[1]), static_cast<int>(imageSize[0]),
                   CV_8UC(imgMsg.getNumChannels()), const_cast<uint8_t*>(imageData)};
  } else {
    // 3D volumes
    int sizes[3]{static_cast<int>(imageSize[1]), static_cast<int>(imageSize[0]),
                 static_cast<int>(imageSize[2])};
    // UE_LOG(SIMPLE, Warning, TEXT("Cannot process volumetric images!"));
    wrap = cv::Mat{3, sizes, CV_8UC(imgMsg.getNumChannels()), const_cast<uint8_t*>(imageData)};
    return;
  }

  if (wrap.total()) {
    wrap.copyTo(ReceivedBackBuffer->m);

    FScopeLock lock(&SwapMutex);
    auto* tmp = ReceivedImage;
    ReceivedImage = ReceivedBackBuffer;
    ReceivedBackBuffer = tmp;
    HasReceivedImage = true;
  }
}
