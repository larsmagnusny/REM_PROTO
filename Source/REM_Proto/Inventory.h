// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "InventoryItem.h"

// Holds inventory items in an array, this can be connected to a player or any object that has an inventory
class REM_PROTO_API Inventory
{
public:
	Inventory();
	~Inventory();

	// Add an item to the inventory
	bool AddItem(InventoryItem* item);

	// Remove an item from the inventory
	void DiscardItem(InventoryItem* item);

	TArray<InventoryItem*> GetInventory();

	FString GetTextureAt(int i);
	int GetSize();

	// Reference to the owner of the inventory
	AActor* Owner = nullptr;

	void Swap(int32 index1, int32 index2);

	int32 GetAvailableIndex();

	InventoryItem* GetItem(int32 index);
private:
	// Where the items get stored, data type defined in InventoryItem.h
	InventoryItem* InventoryStorage[4];
	bool Availablepaces[4]{ true, true, true, true};
};
