// (c) 2019 Technical University of Munich
// Jakob Weiss <jakob.weiss@tum.de>

#include "TransformSubscriberComponent.h"

// Sets default values for this component's properties
UTransformSubscriberComponent::UTransformSubscriberComponent() {
  // Set this component to be initialized when the game starts, and to be ticked every frame.  You
  // can turn these features off to improve performance if you don't need them.
  PrimaryComponentTick.bCanEverTick = true;

  Url = TEXT("tcp://localhost");
  Port = 5555;
  isSubscriberActive = false;
  ReceivedPose = FTransform::Identity;
  Subscriber = nullptr;
}

// Called every frame
void UTransformSubscriberComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                  FActorComponentTickFunction* ThisTickFunction) {
  Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

  // note: a better pattern might be to use TQueue to store the received messages between ticks, as
  // that is lock-free and guarantees not to lose messages.
  FScopeLock lock(&PoseUpdateMutex);
  this->SetRelativeTransform(ReceivedPose);
}

// Called when the game starts
void UTransformSubscriberComponent::BeginPlay() {
  Super::BeginPlay();

  Connect();
}

void UTransformSubscriberComponent::EndPlay(const EEndPlayReason::Type EndPlayReason) {
  Stop();

  Super::EndPlay(EndPlayReason);
}

void UTransformSubscriberComponent::ConnectTo(FString Url, int32 Port) {
  this->Url = Url;
  this->Port = Port;
  Connect();
}

void UTransformSubscriberComponent::Connect() {
  // Minor sanity check for the parameters
  if (Url.IsEmpty() || !Port) return;

  std::string url{TCHAR_TO_UTF8(*Url)};
  std::string address{url + ":" + std::to_string(Port)};
  try {
    Subscriber = std::make_unique<simple::Subscriber<simple_msgs::TransformStamped>>(
        address, [&](const simple_msgs::TransformStamped& tf) {
          auto trans = tf.getTransform().getTranslation();
          auto rot = tf.getTransform().getRotation();
          // to silence cast warning
          auto f = [](double v) { return static_cast<float>(v); };
          auto vec = rot.toVector();

          // TODO: In case we have problems with the rotations, this 3x3 matrix might need to be
          // flipped or one axis inverted to correct for handedness.
          //
          // The current assumption is that the layout of both matrices is the same:
          //
          //		[ (0)  (1)  (2) ]			[ (0) ]
          // vec =	[ (2)  (3)  (4) ]  trans =	[ (1) ]
          //		[ (5)  (6)  (7) ]			[ (2) ]
          //
          //						[ X(0) Y(0) Z(0) W(0) ]
          //						[ X(1) Y(1) Z(1) W(1) ]
          // FMatrix = [X Y Z W] =	[ X(2) Y(2) Z(2) W(2) ]
          //						[  0    0    0    1	  ]
          FVector X{f(vec[0]), f(vec[3]), f(vec[6])};
          FVector Y{f(vec[1]), f(vec[4]), f(vec[7])};
          FVector Z{f(vec[2]), f(vec[5]), f(vec[8])};
          FVector W{f(trans.getX()), f(trans.getY()), f(trans.getZ())};

          FMatrix matrix{X, Y, Z, W};
          FScopeLock lock(&PoseUpdateMutex);
          ReceivedPose.SetFromMatrix(matrix);
        });
    isSubscriberActive = true;
  } catch (std::exception& e) {
    UE_LOG(SIMPLE, Warning, TEXT("Unable to connect: %s"), e.what());
  }
}

void UTransformSubscriberComponent::Stop() {
  Subscriber.reset();

  isSubscriberActive = false;
}
