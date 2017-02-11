// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Wrapper we use for an item stored in an inventory
class REM_PROTO_API InventoryItem
{
public:
	InventoryItem(UStaticMesh* Mesh, FString Name);
	~InventoryItem();
	
	// Store the pointer to the mesh so we can use it later if the player decides to drop the item...
	UStaticMesh* MeshToUse;

	// Store the name
	FString ObjectName;

	// Store the icon of the object so we can show it in the hud...
	UTexture* texture;
};
