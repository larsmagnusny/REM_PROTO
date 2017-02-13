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

	// This is the function all StaticMeshActors inherit from
	// The reason we are not inheriting from UIneractableObject is because that inherits from UActorComponent
	// Items that are visible in the world are StaticMeshActors
	virtual void ActivateObject(AActor* Player);
};
