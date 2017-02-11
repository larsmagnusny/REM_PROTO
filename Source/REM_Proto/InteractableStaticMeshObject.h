// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/StaticMeshActor.h"
#include "InteractableStaticMeshObject.generated.h"

/**
 * 
 */
UCLASS()
class REM_PROTO_API AInteractableStaticMeshObject : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this component's properties
	AInteractableStaticMeshObject();

	virtual void ActivateObject(AActor* Player);
	
	
};
