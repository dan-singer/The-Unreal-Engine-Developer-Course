// Copyright Dan Singer 2017

#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:	

	//How far ahead of the player can we reach in cm
	float Reach = 100.f;
	
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* InputComponent = nullptr;

	//Ray-cast and grab what's in reach
	void Grab();
	//Let go of what we grabbed, if anything
	void Release();

	//Find (assumed) attached physics handle 
	void FindPhysicsHandleComponent();
	//Setup (assumed) attached input component
	void SetupInputComponent();

	//Return hit for first physics body in reach
	FHitResult GetFirstPhysicsBodyInReach() const;

	//Get the vector representing the beginning of our raycast used for grabbing objects
	FVector GetLineTraceStart() const;
	//Get the vector representing the end of our raycast used for grabbing objects
	FVector GetLineTraceEnd() const;
};
