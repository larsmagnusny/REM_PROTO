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