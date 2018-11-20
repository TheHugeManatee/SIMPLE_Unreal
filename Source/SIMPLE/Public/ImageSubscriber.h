// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Runtime/Core/Public/Containers/Queue.h"
#include "Runtime/Engine/Classes/Engine/Texture2D.h"
#include "Runtime/Engine/Classes/Engine/TextureRenderTarget2D.h"

THIRD_PARTY_INCLUDES_START
#include <simple/subscriber.hpp>
#include <simple_msgs/image.hpp>
THIRD_PARTY_INCLUDES_END

#include "UCVUMat.h"

#include <memory>

#include "ImageSubscriber.generated.h"

UCLASS()
class SIMPLE_API AImageSubscriber : public AActor {
  GENERATED_BODY()

public:
  // Sets default values for this actor's properties
  AImageSubscriber();

protected: /* ========== OVERRIDDEN METHODS ========== */
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

  // Called when the actor gets stopped
  virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

  // Event is signaled whenever an image is received
  UFUNCTION(BlueprintImplementableEvent, Category = "SIMPLE|ImageSubscriber")
  void OnFrameReceived();

  virtual void Tick(float DeltaTime) override;

public: /* ========== METHODS ========== */
  /**
   * Connect to a new server. Drops the connection to an existing server.
   * @Note: SIMPLE will try reconnecting if a server is not online, so there is
   *        no need to call this again unless the endpoint is to be changed.
   */
  UFUNCTION(BlueprintCallable, Category = "SIMPLE|ImageSubscriber")
  void ConnectTo(FString Url, int32 Port);

  /**
   * Connect to the currently set Url/Port.
   * @Note: SIMPLE will try reconnecting if a server is not online, so there is
   *        no need to call this again unless the endpoint is to be changed.
   */
  UFUNCTION(BlueprintCallable, Category = "SIMPLE|ImageSubscriber")
  void Connect();

  /**
   * Call this to stop receiving data. After this, isActive will be false.
   */
  UFUNCTION(BlueprintCallable, Category = "SIMPLE|ImageSubscriber")
  void Stop();

public: /* ========== PROPERTIES ========== */
  // The server connection
  UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SIMPLE|ImageSubscriber")
  FString Url;

  // The port to connect to
  UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SIMPLE|ImageSubscriber")
  int32 Port;

  // Whether the subscriber is active. Note: This does NOT tell if the subscriber
  // is actually connected and serving images, but only that the Subscriber has been
  // instantiated. It might still be trying to connect to the publisher..
  UPROPERTY(BlueprintReadOnly, Category = "SIMPLE|ImageSubscriber")
  bool isSubscriberActive;

  // The videos width and height (width, height)
  UPROPERTY(BlueprintReadOnly, Category = "SIMPLE|ImageSubscriber")
  FIntVector ImageSize;

  // This stores the received image
  UPROPERTY(BlueprintReadOnly, Category = "SIMPLE|ImageSubscriber")
  UCVUMat* ReceivedImage;

  // Signals the subscriber to create/update a texture from the Received image (See VideoTexture)
  UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SIMPLE|ImageSubscriber")
  bool UploadTexture;

  UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SIMPLE|ImageSubscriber")
  UTextureRenderTarget2D* VideoTexture;

private: /* ========== INTERNAL ========== */
  void ProcessImage(const simple_msgs::Image<uint8_t>&);

  TAtomic<bool> HasReceivedImage;
  std::unique_ptr<simple::Subscriber<simple_msgs::Image<uint8_t>>> Subscriber;

  UPROPERTY()  // make this a uproperty so it gets GC-handled
  UCVUMat* ReceivedBackBuffer;
  FCriticalSection SwapMutex;
};
