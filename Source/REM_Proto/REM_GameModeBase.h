// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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
	AREM_GameModeBase();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	void SetMainCamera(UCameraComponent* Cam);
	void RayCastArray(FHitResult* Rays, FVector* StartPoints, FVector* EndPoints, int size);
private:
	// Pointer to camera
	UCameraComponent* MainCamera = nullptr;
	FVector2D Points[4][4];
	FVector2D Directions[4] = { FVector2D(1, 1), FVector2D(-1, 1), FVector2D(1, -1), FVector2D(-1, -1) };

	UStaticMeshComponent* LastMeshComponent = nullptr;
};
