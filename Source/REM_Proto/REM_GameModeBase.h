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
private:
	// Pointer to camera
	UCameraComponent* MainCamera = nullptr;
	TArray<InteractableObject> InteractableObjects;
	FVector2D Points[4][4];
	FVector2D Directions[4] = { FVector2D(1, 1), FVector2D(-1, 1), FVector2D(1, -1), FVector2D(-1, -1) };

	UStaticMeshComponent* LastMeshComponent = nullptr;

	
};
