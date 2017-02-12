// Fill out your copyright notice in the Description page of Project Settings.

#include "REM_Proto.h"
#include "InventoryItem.h"

InventoryItem::InventoryItem(UStaticMesh* Mesh, FString Name, FString tex)
{
	MeshToUse = Mesh;
	ObjectName = Name;
	texture = tex;
	UE_LOG(LogTemp, Warning, TEXT("Mesh reference: %s Object Name: %s Texture: %s"), *Mesh->GetName(), *ObjectName, *tex);
}

InventoryItem::~InventoryItem()
{
}
