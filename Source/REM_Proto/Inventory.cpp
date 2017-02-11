// Fill out your copyright notice in the Description page of Project Settings.

#include "REM_Proto.h"
#include "Inventory.h"

Inventory::Inventory()
{

}

Inventory::~Inventory()
{

}

bool Inventory::AddItem(InventoryItem* item)
{
	// Make this more complicated later... but for now, it doesn't need to be...
	InventoryStorage.Add(item);

	return true;
}

void Inventory::DiscardItem(InventoryItem* item)
{

}

void Inventory::PutObjectInWorld(InventoryItem* item)
{

}