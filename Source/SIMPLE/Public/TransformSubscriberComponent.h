// (c) 2018 Jakob Weiss

#pragma once

#include "Components/SceneComponent.h"
#include "CoreMinimal.h"

THIRD_PARTY_INCLUDES_START
#include <simple_msgs/transform_stamped.h>
#include <simple/subscriber.hpp>
THIRD_PARTY_INCLUDES_END

#include <memory>

#include "TransformSubscriberComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SIMPLE_API UTransformSubscriberComponent : public USceneComponent {
  GENERATED_BODY()

public:
  // Sets default values for this component's properties
  UTransformSubscriberComponent();

  // Called every frame
  virtual void TickComponent(float DeltaTime, ELevelTick TickType,
                             FActorComponentTickFunction* ThisTickFunction) override;

protected:
  // Called when the game starts
  virtual void BeginPlay() override;

  virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public: /* ========== METHODS ========== */
        /**
         * Connect to a new server. Drops the connection to an existing server.
         * @Note: SIMPLE will try reconnecting if a server is not online, so there is
         *        no need to call this again unless the endpoint is to be changed.
         */
  UFUNCTION(BlueprintCallable, Category = "SIMPLE|TransformSubscriber")
  void ConnectTo(FString Url, int32 Port);

  /**
   * Connect to the currently set Url/Port.
   * @Note: SIMPLE will try reconnecting if a server is not online, so there is
   *        no need to call this again unless the endpoint is to be changed.
   */
  UFUNCTION(BlueprintCallable, Category = "SIMPLE|TransformSubscriber")
  void Connect();

  /**
   * Call this to stop receiving data. After this, isActive will be false.
   */
  UFUNCTION(BlueprintCallable, Category = "SIMPLE|TransformSubscriber")
  void Stop();

public: /* ========== PROPERTIES ========== */
  // The server connection
  UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SIMPLE|TransformSubscriber")
  FString Url;

  // The port to connect to
  UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SIMPLE|TransformSubscriber")
  int32 Port;

  // Whether the subscriber is active. Note: This does NOT tell if the subscriber
  // is actually connected and serving images, but only that the Subscriber has been
  // instantiated. It might still be trying to connect to the publisher..
  UPROPERTY(BlueprintReadOnly, Category = "SIMPLE|ImageSubscriber")
  bool isSubscriberActive;

private:
  std::unique_ptr<simple::Subscriber<simple_msgs::TransformStamped>> Subscriber;

  FCriticalSection PoseUpdateMutex;  ///< Mutex guarding access to the following FMatrix
  FTransform ReceivedPose;  ///< The matrix received from the receiver thread to be used in the tick
};
