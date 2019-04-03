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
  , Url{TEXT("")}
  , Port{0}
  , isSubscriberActive{false}
  , ImageSize{0, 0, 0}
  , VoxelSize{0.0}
  , ImageOrigin{0.0}
  , ImageRotation{}
  , ReceivedImage{nullptr} 
  , VideoTexture{nullptr}
  , Subscriber{nullptr}
  , ReceivedBackBuffer{nullptr}
	, ReceivedExchangeBuffer{ nullptr } {
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
  Super::Tick(DeltaTime);

  if (HasReceivedImage) {
    {  // copy/swap the the data and clear received flag
      FScopeLock lock(&SwapMutex);
      Swap(ReceivedImage, ReceivedExchangeBuffer);
      ImageSize = ImageSizeBackBuffer;
      VoxelSize = VoxelSizeBackBuffer;
      ImageOrigin = ImageOriginBackBuffer;
      ImageRotation = ImageRotationBackBuffer;

      HasReceivedImage = false;
    }
    if (!ReceivedImage) {
      UE_LOG(SIMPLE, Error, TEXT("Received image turned out empty!"));
    } else {
      if (UploadTexture) {
        ReceivedImage->ToRenderTarget(VideoTexture, false);
      }

      OnFrameReceived();
    }
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
    isSubscriberActive = true;
  } catch (std::exception& e) {
    UE_LOG(SIMPLE, Warning, TEXT("Unable to connect: %s"), UTF8_TO_TCHAR(e.what()));
  }
}

void AImageSubscriber::Stop() {
  Subscriber.reset();

  isSubscriberActive = false;
}

void AImageSubscriber::ProcessImage(const simple_msgs::Image<uint8_t>& imgMsg) {
  auto& header = imgMsg.getHeader();
  auto* imageData = imgMsg.getImageData();
  auto imageSize = imgMsg.getImageDimensions();
  auto imageVoxelSize = imgMsg.getSpacing();
  auto imagePos = imgMsg.getImageOrigin().getPosition();
  auto imageRot = imgMsg.getImageOrigin().getQuaternion();

  cv::Mat wrap;
  if (imageSize[2] == 1) {
    // 2D images
    // Wrap in a cv::Mat and copy the buffer
    wrap = cv::Mat{static_cast<int>(imageSize[1]), static_cast<int>(imageSize[0]),
                   CV_8UC(imgMsg.getNumChannels()), const_cast<uint8_t*>(imageData)};
  } else {
    // 3D volumes
    int sizes[3]{static_cast<int>(imageSize[2]), static_cast<int>(imageSize[1]),
                 static_cast<int>(imageSize[0])};
    UE_LOG(SIMPLE, Warning, TEXT("Received a volume of %d %d %d!"), imageSize[0], imageSize[1],
           imageSize[2]);
    wrap = cv::Mat{3, sizes, CV_8UC(imgMsg.getNumChannels()), const_cast<uint8_t*>(imageData)};
  }

  if (wrap.total()) {
    try {
      // Create the back buffer if it's empty
      if (!ReceivedBackBuffer) {
        ReceivedBackBuffer = NewObject<UCVUMat>();
      }
      wrap.copyTo(ReceivedBackBuffer->m);

      // swap data and fill back buffer info
      FScopeLock lock(&SwapMutex);
      Swap(ReceivedBackBuffer, ReceivedExchangeBuffer);
      ImageSizeBackBuffer =
          FIntVector{int32(imageSize[0]), int32(imageSize[1]), int32(imageSize[2])};
      VoxelSizeBackBuffer =
          FVector{float(imageVoxelSize[0]), float(imageVoxelSize[1]), float(imageVoxelSize[2])};
      ImageOriginBackBuffer =
          FVector{float(imagePos.getX()), float(imagePos.getY()), float(imagePos.getZ())};
      ImageRotationBackBuffer = FQuat{float(imageRot.getX()), float(imageRot.getY()),
                                      float(imageRot.getZ()), float(imageRot.getW())};

      // set the flag so the tick() will fetch the data
      HasReceivedImage = true;
    } catch (std::exception& e) {
      UE_LOG(SIMPLE, Error, TEXT("Error copying the received image: %s"), UTF8_TO_TCHAR(e.what()))
    };
  }
}
