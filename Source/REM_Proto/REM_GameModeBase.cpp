// Fill out your copyright notice in the Description page of Project Settings.

#include "REM_Proto.h"
#include "REM_GameModeBase.h"
#include "MainCharacter.h"
#include "REM_HUD.h"

AREM_GameModeBase::AREM_GameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;

	DefaultPawnClass = nullptr;

	HUDClass = AREM_HUD::StaticClass();
}

void AREM_GameModeBase::BeginPlay()
{
	Super::BeginPlay();

	float Scale = 2.0f;

	for (int32 i = 0; i < 4; i++)
	{
		for (int32 j = 0; j < 4; j++)
		{
			Points[i][j] = Directions[j] * Scale;
		}
	}
}

void AREM_GameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MainCamera)
	{
		// Raycast 16 rays from the camera to check if the player can see a wall.

		FHitResult Result;

		RayCastArray(Result);

		FVector HitPoint = Result.ImpactPoint;

		FVector HitVector = HitPoint - MainCamera->GetComponentLocation();

		double MagHit = HitVector.Size();
		double CamChar = 730;

		if (MagHit < CamChar) // Means we are hitting a wall....
		{
			AStaticMeshActor* HitActor = Cast<AStaticMeshActor>(Result.GetActor());

			if (!HitActor)
				return;

			UStaticMeshComponent* MeshComponent = Cast<UStaticMeshComponent>(HitActor->GetComponentByClass(UStaticMeshComponent::StaticClass()));
			if (!MeshComponent)
				return;

			if (MeshComponent != LastMeshComponent && !LastMeshComponent)
			{
				MeshComponent->SetVisibility(false, true);

				MeshComponent->SetCollisionProfileName(FName("InvisibleWall"));

				LastMeshComponent = MeshComponent;
			}
			else if (LastMeshComponent)
			{
				LastMeshComponent->SetVisibility(true, true);
				LastMeshComponent->SetCollisionProfileName(FName("BlockAll"));

				MeshComponent->SetVisibility(false, true);

				MeshComponent->SetCollisionProfileName(FName("InvisibleWall"));

				LastMeshComponent = MeshComponent;
			}
		}
		else
		{
			if (LastMeshComponent)
			{
				LastMeshComponent->SetVisibility(true, true);
				LastMeshComponent->SetCollisionProfileName(FName("BlockAll"));
				LastMeshComponent = nullptr;
			}
		}
	}
}

void AREM_GameModeBase::RayCastArray(FHitResult& Ray)
{
	GetWorld()->LineTraceSingleByChannel(Ray, MainCamera->GetComponentLocation(), MainCamera->GetComponentLocation() + MainCamera->GetForwardVector()*1000, ECollisionChannel::ECC_MAX);
}

void AREM_GameModeBase::SetMainCamera(UCameraComponent* Cam)
{
	MainCamera = Cam;
}