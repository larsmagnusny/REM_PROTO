// Fill out your copyright notice in the Description page of Project Settings.

#include "REM_Proto.h"
#include "InteractableObject.h"


// Sets default values for this component's properties
UInteractableObject::UInteractableObject()
{

}

void UInteractableObject::ActivateObject()
{
	// Do nothing here, but do something in the classes that inherit it...
	UE_LOG(LogTemp, Error, TEXT("Called from InteractibleObject?!"));
}
