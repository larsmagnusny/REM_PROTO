// Fill out your copyright notice in the Description page of Project Settings.

#include "REM_Proto.h"
#include "InventoryItem.h"

InventoryItem::InventoryItem(UStaticMesh* Mesh, FString Name)
{
	MeshToUse = Mesh;
	ObjectName = Name;

	UE_LOG(LogTemp, Warning, TEXT("Mesh reference: %s Object Name: %s"), *Mesh->GetName(), *ObjectName);
}

InventoryItem::~InventoryItem()
{
}
