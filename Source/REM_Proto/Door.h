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

	virtual void ActivateObject() override;

	void OpenDoor();
	void CloseDoor();
		
private:
	bool DoorOpen = false;
};
