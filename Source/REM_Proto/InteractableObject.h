// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "InteractableObject.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REM_PROTO_API UInteractableObject : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractableObject();

	// The function all interactible object components inherit
	// This can be triggered from MainCharacter.cpp on all objects that are interactible and inherit from this class
	virtual void ActivateObject();
};
