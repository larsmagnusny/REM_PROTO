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

	static ConstructorHelpers::FObjectFinder<UClass> Blueprint(TEXT("Class'/Game/Blueprints/PlayerController.PlayerController_C'"));

	if (Blueprint.Succeeded())
	{
		PlayerControllerClass = (UClass*)Blueprint.Object;
	}
}

void AREM_GameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

void AREM_GameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AREM_GameModeBase::RayCastArray(FHitResult& Ray)
{
	GetWorld()->LineTraceSingleByChannel(Ray, MainCamera->GetComponentLocation(), MainCamera->GetComponentLocation() + MainCamera->GetForwardVector()*1000, ECollisionChannel::ECC_MAX);
}

<<<<<<< HEAD
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
=======
void AREM_GameModeBase::SetMainCamera(UCameraComponent* Cam)
{
	MainCamera = Cam;
}

bool AREM_GameModeBase::IsInteractible(AActor* Actor)
{
	for (int32 i = 0; i < InteractableObjects.Num(); i++)
	{
		if (InteractableObjects[i].ParentObject == Actor)
			return true;
	}

	return false;
}

void AREM_GameModeBase::AddInteractableObject(AActor* Actor, UInteractableObject* Object)
{
	InteractableObject Obj;
	Obj.ParentObject = Actor;
	Obj.Object = Object;
	InteractableObjects.Add(Obj);
}

void AREM_GameModeBase::AddInteractableObject(AActor* Actor, AInteractableStaticMeshObject* Object)
{
	InteractableObject Obj;
	Obj.ParentObject = Actor;
	Obj.StaticMeshObject = Object;
	InteractableObjects.Add(Obj);
}

void AREM_GameModeBase::RemoveInteractableObject(AActor* Actor)
{
	for (int32 i = 0; i < InteractableObjects.Num(); i++)
	{
		if (InteractableObjects[i].ParentObject == Actor)
		{
			InteractableObjects.RemoveAt(i);
			break;
		}
	}
}

UInteractableObject* AREM_GameModeBase::GetInteractor(AActor* Actor)
{
	for (int32 i = 0; i < InteractableObjects.Num(); i++)
	{
		if (InteractableObjects[i].ParentObject == Actor)
			return InteractableObjects[i].Object;
	}

	return nullptr;
}

AInteractableStaticMeshObject* AREM_GameModeBase::GetStaticMeshInteractor(AActor* Actor)
{
	for (int32 i = 0; i < InteractableObjects.Num(); i++)
	{
		if (InteractableObjects[i].ParentObject == Actor)
			return InteractableObjects[i].StaticMeshObject;
>>>>>>> c45fd19053385ff5e2237c99a5c2d2e1864166b1
	}

	return nullptr;
}

<<<<<<< HEAD
void AREM_GameModeBase::RayCastArray(FHitResult* Rays, FVector* StartPoints, FVector* EndPoints, int size)
{
	for (int32 i = 0; i < size; ++i)
	{
		FVector Start = StartPoints[i];
		FVector End = EndPoints[i];

		GetWorld()->LineTraceSingleByChannel(Rays[i], Start, End, ECollisionChannel::ECC_MAX);
		DrawDebugLine(GetWorld(), Start, Rays[i].ImpactPoint, FColor(255, 0, 0, 255), false, -1.0f, 0, 10.0f);
	}
=======
ACharacter* AREM_GameModeBase::GetMainCharacter()
{
	return MainCharacter;
>>>>>>> c45fd19053385ff5e2237c99a5c2d2e1864166b1
}

void AREM_GameModeBase::SetMainCharacter(ACharacter* Char)
{
	MainCharacter = Char;
}