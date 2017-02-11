// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Wrapper we use for an item stored in an inventory
class REM_PROTO_API InventoryItem
{
public:
	InventoryItem(UStaticMesh* Mesh, FString Name);
	~InventoryItem();
	
	UStaticMesh* MeshToUse;
	FString ObjectName;
	UTexture* texture;
};
