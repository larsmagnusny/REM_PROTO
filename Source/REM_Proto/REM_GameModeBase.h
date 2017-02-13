// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "InteractableObject.h"
#include "InteractableStaticMeshObject.h"
#include "Inventory.h"
#include "GameFramework/GameModeBase.h"
#include "REM_GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class REM_PROTO_API AREM_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	struct InteractableObject
	{
		AActor* ParentObject = nullptr;
		UInteractableObject* Object = nullptr;
		AInteractableStaticMeshObject* StaticMeshObject = nullptr;
	};

	AREM_GameModeBase();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	void SetMainCamera(UCameraComponent* Cam);

	void RayCastArray(FHitResult& Ray);

	// We need to check if we can highlight an object!
	void AddInteractableObject(AActor* Actor, UInteractableObject* Object = nullptr);
	void AddInteractableObject(AActor* Actor, AInteractableStaticMeshObject* Object = nullptr);
	void RemoveInteractableObject(AActor* Actor);
	bool IsInteractible(AActor* Actor);
	UInteractableObject* GetInteractor(AActor* Actor);
	AInteractableStaticMeshObject* GetStaticMeshInteractor(AActor* Actor);
	
	UFUNCTION(BlueprintCallable, Category="Character")
	ACharacter* GetMainCharacter();

	void SetMainCharacter(ACharacter* Char);

	// Spawn the object in the world and remove it from the inventory
	void PutObjectInWorld(InventoryItem* item, FVector2D Hitpoint);
private:
	// Pointer to camera
	UCameraComponent* MainCamera = nullptr;
	TArray<InteractableObject> InteractableObjects;

	UStaticMeshComponent* LastMeshComponent = nullptr;

	// Pointer to our main character
	ACharacter* MainCharacter = nullptr;
};
