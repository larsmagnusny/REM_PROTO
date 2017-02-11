// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "InventoryItem.h"

// Holds inventory items in an array, this can be connected to a player or any object that has an inventory
class REM_PROTO_API Inventory
{
public:
	Inventory();
	~Inventory();

	bool AddItem(InventoryItem* item);
	void DiscardItem(InventoryItem* item);
	void PutObjectInWorld(InventoryItem* item);

	// Reference to the owner of the inventory
	AActor* Owner = nullptr;
private:
	TArray<InventoryItem*> InventoryStorage;
};
