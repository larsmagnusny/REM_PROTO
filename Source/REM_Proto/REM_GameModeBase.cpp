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
void AREM_GameModeBase::RemoveInteractableObject(AActor* Actor)
{
	
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