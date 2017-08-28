// Copyright Dan Singer 2017

#include "WinDetection.h"


// Sets default values for this component's properties
UWinDetection::UWinDetection()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWinDetection::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UWinDetection::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	if (HasWon) return;

	TArray<AActor*> Actors;
	GetOwner()->GetRootPrimitiveComponent()->GetOverlappingActors(Actors);
	if (Actors.Num() > 0)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, "You Won!!");
		}
		HasWon = true;
	}
}

