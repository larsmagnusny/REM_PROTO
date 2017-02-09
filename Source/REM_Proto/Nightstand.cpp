// Fill out your copyright notice in the Description page of Project Settings.

#include "REM_Proto.h"
#include "Nightstand.h"


// Sets default values for this component's properties
UNightstand::UNightstand()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UNightstand::BeginPlay()
{
	Super::BeginPlay();

	// ...
	AREM_GameModeBase* GameMode = Cast<AREM_GameModeBase>(GetWorld()->GetAuthGameMode());

	GameMode->AddInteractableObject(GetOwner(), Cast<UInteractableObject>(this));
}


// Called every frame
void UNightstand::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void UNightstand::ActivateObject()
{

}