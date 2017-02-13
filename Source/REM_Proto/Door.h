// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "InteractableObject.h"
#include "Components/ActorComponent.h"
#include "Door.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REM_PROTO_API UDoor : public UInteractableObject
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoor();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	// Inherited from UInteractableObject so we don't have to include 1000 files to interact with 1000 different objects...
	virtual void ActivateObject() override;

	void OpenDoor();
	void CloseDoor();
		
private:
	FRotator InitialRotation;
	float RotationOffset = 0.f;
	bool DoorOpen = false;
};
