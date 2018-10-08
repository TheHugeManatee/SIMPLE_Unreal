// Fill out your copyright notice in the Description page of Project Settings.

#include "ImageSubscriber.h"

#include "SIMPLE_Common.h"

#include "PushUEMacros.h"
// this is a safe space..
#include <simple/client.hpp>
#include <simple_msgs/int.hpp>
// outside here is UE macro wild wild west
#include "PopUEMacros.h"

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
  PrimaryActorTick.bCanEverTick = false;
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
    Subscriber.reset(new simple::Subscriber<simple_msgs::Image<uint8_t>>{
        address, [&](const simple_msgs::Image<uint8_t>& img) { ProcessImage(img); }});
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

  if (imageSize[2] != 1) {
    UE_LOG(SIMPLE, Warning, TEXT("Cannot process volumetric images!"));
    return;
  }

  if (!ReceivedImage) {
    ReceivedImage = NewObject<UCVUMat>();
  }

  // Wrap in a cv::Mat and copy the buffer
  cv::Mat wrap{static_cast<int>(imageSize[1]), static_cast<int>(imageSize[0]),
               CV_8UC(imgMsg.getNumChannels()), const_cast<uint8_t*>(imageData)};
  wrap.copyTo(ReceivedImage->m);

  // If the image actually has data and we are supposed to, upload to a texture
  if (wrap.total() && CreateTexture) {
    VideoTexture = ReceivedImage->toTexture(VideoTexture, false);

    if (RenderTarget) ReceivedImage->toRenderTarget(RenderTarget, false);
  }
}
