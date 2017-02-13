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

		const int32 size = 6;
		FHitResult Results[size];

		// Create 4 rays inner in a square
		// Create 4 rays outside of that and so on...

		FVector Center = MainCamera->GetComponentLocation();
		FTransform MainCameraTransform = MainCamera->GetComponentTransform();

		FVector StartPoints[size];
		FVector EndPoints[size];

		float length = 100.0f;

		StartPoints[0] = FVector::ZeroVector;
		StartPoints[1] = Center + FVector(1, 0, 0)*length;
		StartPoints[2] = Center + FVector(0, 1, 0)*length;
		StartPoints[3] = Center + FVector(1, 1, 0)*length;
		StartPoints[4] = Center + FVector(-1, 0, 0)*length;
		StartPoints[5] = Center + FVector(0, -1, 0)*length;
		StartPoints[5] = Center + FVector(-1, -1, 0)*length;

		for (int32 i = 0; i < size; i++)
		{
			StartPoints[i] = MainCameraTransform.TransformPosition(StartPoints[i]);
		}

		float EndLength = 10000.0f;

		for (int32 i = 0; i < size; i++)
		{
			EndPoints[i] = StartPoints[i] + MainCamera->GetForwardVector()*EndLength;
		}


		RayCastArray(Results, StartPoints, EndPoints, size);

		for (int32 i = 0; i < size; i++)
		{
			FHitResult Result = Results[i];
			FVector HitPoint = Result.ImpactPoint;

			FVector HitVector = HitPoint - MainCamera->GetComponentLocation();

			double MagHit = HitVector.Size();

			UE_LOG(LogTemp, Warning, TEXT("%s"), *FString::SanitizeFloat(MagHit));

			double CamChar = 1500;

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
}

void AREM_GameModeBase::RayCastArray(FHitResult* Rays, FVector* StartPoints, FVector* EndPoints, int size)
{
	for (int32 i = 0; i < size; ++i)
	{
		FVector Start = StartPoints[i];
		FVector End = EndPoints[i];

		GetWorld()->LineTraceSingleByChannel(Rays[i], Start, End, ECollisionChannel::ECC_MAX);
		DrawDebugLine(GetWorld(), Start, Rays[i].ImpactPoint, FColor(255, 0, 0, 255), false, -1.0f, 0, 10.0f);
	}
}

void AREM_GameModeBase::SetMainCamera(UCameraComponent* Cam)
{
	MainCamera = Cam;
}