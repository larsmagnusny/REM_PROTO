// Fill out your copyright notice in the Description page of Project Settings.

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White,text)

#include "REM_Proto.h"
#include "InventoryItemObject.h"
#include "MainCharacter.h"

AInventoryItemObject::AInventoryItemObject()
{
	
}

// Called when the game starts
void AInventoryItemObject::BeginPlay()
{
	InitObject();
}

// Called every frame
void AInventoryItemObject::Tick(float DeltaTime)
{

}

// Called when the player clicks on the object...
void AInventoryItemObject::ActivateObject(AActor* Player)
{
	UE_LOG(LogTemp, Warning, TEXT("Player has clicked on an inventory item object"));

	// Add this item to the inventory...
	Cast<AMainCharacter>(Player)->AddItemToInventory(ToInventoryItem());

	// Remove this item from the world when added to the inventory...
	RemoveFromWorld();

	FString InvMessage = ObjectName + "Added to inventory!";

	print(InvMessage);
}

void AInventoryItemObject::InitObject()
{
	// Set the mesh and material/s
	UStaticMeshComponent* MeshComponent = Cast<UStaticMeshComponent>(GetComponentByClass(UStaticMeshComponent::StaticClass()));

	// Set Mesh
	MeshComponent->SetStaticMesh(MeshToUse);

	// Set Materials
	for (int32 i = 0; i < MaterialsToUse.Num(); i++)
		MeshComponent->SetMaterial(i, MaterialsToUse[i]);
	

	// Make the object simulate physics...
	MeshComponent->SetMobility(EComponentMobility::Movable);
	MeshComponent->SetSimulatePhysics(true);
	MeshComponent->bGenerateOverlapEvents = true;

	// Make the object Interactable
	GameMode = Cast<AREM_GameModeBase>(GetWorld()->GetAuthGameMode());

	GameMode->AddInteractableObject(Cast<AActor>(this), Cast<AInteractableStaticMeshObject>(this));
}

void AInventoryItemObject::RemoveFromWorld()
{
	if (GameMode)
	{
		GameMode->RemoveInteractableObject(Cast<AActor>(this));

		Destroy();
	}
}

InventoryItem* AInventoryItemObject::ToInventoryItem()
{
	InventoryItem* Ret = new InventoryItem(MeshToUse, ObjectName, Icon);

	return Ret;
}