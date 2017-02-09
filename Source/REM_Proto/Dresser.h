// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "InteractableObject.h"
#include "Components/ActorComponent.h"

#include "REM_GameModeBase.h"
#include "Dresser.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REM_PROTO_API UDresser : public UInteractableObject
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDresser();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	virtual void ActivateObject() override;
	
};
