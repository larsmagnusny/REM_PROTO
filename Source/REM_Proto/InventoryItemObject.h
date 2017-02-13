// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "InteractableStaticMeshObject.h"
#include "REM_GameModeBase.h"
#include "InventoryItem.h"
#include "Engine/StaticMeshActor.h"
#include "InventoryItemObject.generated.h"

// Class for inventory item that exists in the world
UCLASS()
class REM_PROTO_API AInventoryItemObject : public AInteractableStaticMeshObject
{
	GENERATED_BODY()
public:
	AInventoryItemObject();

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called when the player clicks on the object...
	virtual void ActivateObject(AActor* Player) override;

	InventoryItem* ToInventoryItem();
	
	void InitObject();

	void RemoveFromWorld();

	UPROPERTY(EditAnywhere)
	UStaticMesh* MeshToUse;
	UPROPERTY(EditAnywhere)
	TArray<UMaterial*> MaterialsToUse;
	UPROPERTY(EditAnywhere)
	FString ObjectName;
	UPROPERTY(EditAnywhere)
	FString Icon;

	bool needsDelete = false;
	
private:
	AREM_GameModeBase* GameMode = nullptr;
	
};
