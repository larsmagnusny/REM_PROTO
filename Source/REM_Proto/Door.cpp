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

	// Register the door as an interactible object in the gamemodeclass...
	AREM_GameModeBase* GameMode = Cast<AREM_GameModeBase>(GetWorld()->GetAuthGameMode());

	GameMode->AddInteractableObject(GetOwner(), Cast<UInteractableObject>(this));
}


// Called every frame
void UDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void UDoor::ActivateObject()
{
	print("Door is locked! There must be a key around here somewhere!");
}

void UDoor::OpenDoor()
{
	UE_LOG(LogTemp, Error, TEXT("Door Event Called!"));
	DoorOpen = true;
}

void UDoor::CloseDoor()
{
	DoorOpen = false;
}

