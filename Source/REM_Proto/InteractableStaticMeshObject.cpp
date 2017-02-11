// Fill out your copyright notice in the Description page of Project Settings.

#include "REM_Proto.h"
#include "InteractableStaticMeshObject.h"




// Sets default values for this component's properties
AInteractableStaticMeshObject::AInteractableStaticMeshObject()
{
	// Register the door as an interactible object in the gamemodeclass...

}

void AInteractableStaticMeshObject::ActivateObject(AActor* Player)
{
	// Do nothing here, but do something in the classes that inherit it...
	UE_LOG(LogTemp, Error, TEXT("Called from AInteractableStaticMeshObject?!"));
}
