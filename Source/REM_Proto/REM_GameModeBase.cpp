// Fill out your copyright notice in the Description page of Project Settings.

#include "REM_Proto.h"
#include "REM_GameModeBase.h"
#include "MainCharacter.h"
#include "REM_HUD.h"
#include "InventoryItemObject.h"

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
	}

	return nullptr;
}

ACharacter* AREM_GameModeBase::GetMainCharacter()
{
	return MainCharacter;
}

void AREM_GameModeBase::SetMainCharacter(ACharacter* Char)
{
	MainCharacter = Char;
}

void AREM_GameModeBase::PutObjectInWorld(InventoryItem* item, FVector2D Hitpoint)
{
	if (item)
	{
		UE_LOG(LogTemp, Error, TEXT("Should try to spawn item into world now! texture: %s"), *item->texture);

		FVector CharacterLocation = MainCharacter->GetActorLocation();

		FVector2D dir =  Hitpoint - FVector2D(CharacterLocation);
		dir.Normalize();

		FTransform t;
		t.SetScale3D(FVector(1.0f, 1.0f, 1.0f));
		t.SetLocation(CharacterLocation + 50*FVector(dir, 0.5));

		auto MyDeferredActor = Cast<AInventoryItemObject>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, AInventoryItemObject::StaticClass(), t));

		if (MyDeferredActor)
		{
			MyDeferredActor->DeferredSpawn = true;
			MyDeferredActor->MeshToUse = item->MeshToUse;
			MyDeferredActor->Icon = item->texture;
			MyDeferredActor->ObjectName = item->ObjectName;
			MyDeferredActor->InitObject();


			UGameplayStatics::FinishSpawningActor(MyDeferredActor, t);

			Cast<AMainCharacter>(MainCharacter)->DiscardItem(item);
		}
	}
}
