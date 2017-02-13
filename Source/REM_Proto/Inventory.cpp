// Fill out your copyright notice in the Description page of Project Settings.

#include "REM_Proto.h"
#include "Inventory.h"

Inventory::Inventory()
{
	for (int32 i = 0; i < 4; i++)
		InventoryStorage[i] = nullptr;
}

Inventory::~Inventory()
{

}

bool Inventory::AddItem(InventoryItem* item)
{
	// Make this more complicated later... but for now, it doesn't need to be...
	bool ret = true;

	int32 Space = GetAvailableIndex();

	if (Space >= 0)
	{
		InventoryStorage[Space] = item;
		Availablepaces[Space] = false;
		return true;

		UE_LOG(LogTemp, Error, TEXT("Item added to inventory! At slot num: %s"), *FString::FromInt(Space));
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Could not add item to inventory!"));
		return false;
	}
}

void Inventory::DiscardItem(InventoryItem* item)
{
	for (int32 i = 0; i < 4; i++)
	{
		if (InventoryStorage[i] == item)
		{
			InventoryStorage[i] = nullptr;
			Availablepaces[i] = true;
		}
	}
}

FString Inventory::GetTextureAt(int i)
{
	if (i <= 3 && InventoryStorage[i])
		return InventoryStorage[i]->texture;
	else
		return "";
}
int Inventory::GetSize()
{
	return 4;
}

void Inventory::Swap(int32 index1, int32 index2)
{
	InventoryItem* item1 = InventoryStorage[index2];
	InventoryStorage[index2] = InventoryStorage[index1];
	InventoryStorage[index1] = item1;

	bool boolitem1 = Availablepaces[index2];

	Availablepaces[index2] = Availablepaces[index1];
	Availablepaces[index1] = boolitem1;
}

int32 Inventory::GetAvailableIndex()
{
	for (int32 i = 0; i < 4; i++)
	{
		if (Availablepaces[i])
		{
			return i;
		}
	}

	return -1;
}

InventoryItem* Inventory::GetItem(int32 index)
{
	return InventoryStorage[index];
}