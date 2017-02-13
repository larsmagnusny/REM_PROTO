// Fill out your copyright notice in the Description page of Project Settings.

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White,text)

#include "REM_Proto.h"
#include "Door.h"
#include "REM_GameModeBase.h"
#include "InteractableObject.h"
#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>



// Sets default values for this component's properties
UDoor::UDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoor::BeginPlay()
{
	Super::BeginPlay();

	// Get a pointer to the GameMode class so you can add this class instance as an "interactor" ( Something the player can click )
	AREM_GameModeBase* GameMode = Cast<AREM_GameModeBase>(GetWorld()->GetAuthGameMode());

	GameMode->AddInteractableObject(GetOwner(), Cast<UInteractableObject>(this));

	// Store the initial rotation of the door so it can go back to this rotation after being closed
	InitialRotation = GetOwner()->GetActorRotation();
}


// Called every frame
void UDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// Get the current rotation of the door
	FRotator rotator = GetOwner()->GetActorRotation();

	// If the door is being opened open the door partially every frame untill it has a 90 degree difference in rotation from the original position
	if (DoorOpen)
	{
		if (RotationOffset > -90.0f)
		{
			RotationOffset -= 200*DeltaTime;
		}
		else {
			RotationOffset = -90.0f;
		}
	}
	else // If the door is being closed partially subtract every frame untill it has a 0 degree rotation...
	{
		if (RotationOffset < 0)
		{
			RotationOffset += 200 * DeltaTime;
		}
		else
		{
			RotationOffset = 0.f;
		}
	}

	// Set the rotation of the door
	rotator.Yaw = InitialRotation.Yaw + RotationOffset;
	GetOwner()->SetActorRotation(rotator);
}

void UDoor::ActivateObject()
{
	// If the player has activated the door by clicking on it toggle dooropen
	//print("Door is locked! There must be a key around here somewhere!");

	if (!DoorOpen)
		OpenDoor();
	else if (DoorOpen)
		CloseDoor();
}

void UDoor::OpenDoor()
{
	DoorOpen = true;
}

void UDoor::CloseDoor()
{
	DoorOpen = false;
}

