// Fill out your copyright notice in the Description page of Project Settings.

#include "REM_Proto.h"
#include "MainCharacter.h"
#include "AI/Navigation/NavigationSystem.h"
#include "InteractableObject.h"


// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->RelativeRotation = FRotator(-60.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = true; // Don't want to pull camera in when it collides with level

										  // Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetFirstPlayerController()->SetViewTarget(this);	// Switch to the cameracomponent attached to this player
	SetupPlayerInputComponent(GetWorld()->GetFirstPlayerController()->InputComponent);

	SkeletalMeshComponent = Cast<USkeletalMeshComponent>(GetComponentByClass(USkeletalMeshComponent::StaticClass()));

	GameMode = Cast<AREM_GameModeBase>(GetWorld()->GetAuthGameMode());
	GameMode->SetMainCamera(TopDownCameraComponent);
	
	// Initialize Inventory
	PlayerInventory = new Inventory();
}

// Called every frame
void AMainCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (KeyboardControlled)
	{
		UpdateRotation();
		UpdateMovement();
	}

	if (MouseControlled)
	{
		FHitResult Hit;
		GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility), false, Hit);

		if (Hit.GetActor())
		{
			if (Hit.GetActor()->IsA(AStaticMeshActor::StaticClass()))
			{
				AStaticMeshActor* OurActor = Cast<AStaticMeshActor>(Hit.GetActor());
				UStaticMeshComponent* MeshComponent = Cast<UStaticMeshComponent>(OurActor->GetComponentByClass(UStaticMeshComponent::StaticClass()));
				
				
				if (MeshComponent != LastComponentMousedOver)
				{
					if (LastComponentMousedOver)
						LastComponentMousedOver->SetRenderCustomDepth(false);
				}

				if (GameMode->IsInteractible(Hit.GetActor()))
				{
					MeshComponent->SetRenderCustomDepth(true);
					LastComponentMousedOver = MeshComponent;
				}
			}
		}
		else {
			if (LastComponentMousedOver)
				LastComponentMousedOver->SetRenderCustomDepth(false);
			LastComponentMousedOver = nullptr;
		}

		if (MouseMove)
		{
			UNavigationSystem* const NavSys = GetWorld()->GetNavigationSystem();
			float const Distance = FVector::Dist(MoveTo, GetActorLocation());

			if (NavSys && (Distance > 80.0f))
			{
				NavSys->SimpleMoveToLocation(Controller, MoveTo);
			}
			else {
				MouseMove = false;

				if (DelayActivate)
				{
					UE_LOG(LogTemp, Warning, TEXT("Got interactor, sending activate command..."));
					if (DelayActivateObject)
					{
						DelayActivateObject->ActivateObject();
						DelayActivateObject = nullptr;
					}
					if (DelayActivateStaticMeshObject)
					{
						DelayActivateStaticMeshObject->ActivateObject(Cast<AActor>(this));
						DelayActivateStaticMeshObject = nullptr;
					}
					DelayActivate = false;
				}
			}
		}
	}
}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(FName("Left"), EInputEvent::IE_Pressed, this, &AMainCharacter::KeyboardStartMoveLeft);
	PlayerInputComponent->BindAction(FName("Left"), EInputEvent::IE_Released, this, &AMainCharacter::KeyboardStopMoveLeft);

	PlayerInputComponent->BindAction(FName("Right"), EInputEvent::IE_Pressed, this, &AMainCharacter::KeyboardStartMoveRight);
	PlayerInputComponent->BindAction(FName("Right"), EInputEvent::IE_Released, this, &AMainCharacter::KeyboardStopMoveRight);

	PlayerInputComponent->BindAction(FName("Up"), EInputEvent::IE_Pressed, this, &AMainCharacter::KeyboardStartMoveUp);
	PlayerInputComponent->BindAction(FName("Up"), EInputEvent::IE_Released, this, &AMainCharacter::KeyboardStopMoveUp);

	PlayerInputComponent->BindAction(FName("Down"), EInputEvent::IE_Pressed, this, &AMainCharacter::KeyboardStartMoveDown);
	PlayerInputComponent->BindAction(FName("Down"), EInputEvent::IE_Released, this, &AMainCharacter::KeyboardStopMoveDown);

	PlayerInputComponent->BindAxis(FName("AxisLeftRight"), this, &AMainCharacter::AxisMoveLeftRight);
	PlayerInputComponent->BindAxis(FName("AxisUpDown"), this, &AMainCharacter::AxisMoveUpDown);

	PlayerInputComponent->BindAction(FName("MouseClickLeft"), EInputEvent::IE_Pressed, this, &AMainCharacter::MouseLeftClick);
	PlayerInputComponent->BindAction(FName("MouseClickRight"), EInputEvent::IE_Pressed, this, &AMainCharacter::MouseRightClick);
}

void AMainCharacter::KeyboardStartMoveLeft()
{
	KeyboardMovingLeft = true;
}
void AMainCharacter::KeyboardStopMoveLeft()
{
	KeyboardMovingLeft = false;
}

void AMainCharacter::KeyboardStartMoveRight()
{
	KeyboardMovingRight = true;
}
void AMainCharacter::KeyboardStopMoveRight()
{
	KeyboardMovingRight = false;
}

void AMainCharacter::KeyboardStartMoveUp()
{
	KeyboardMovingUp = true;
}
void AMainCharacter::KeyboardStopMoveUp()
{
	KeyboardMovingUp = false;
}

void AMainCharacter::KeyboardStartMoveDown()
{
	KeyboardMovingDown = true;
}
void AMainCharacter::KeyboardStopMoveDown()
{
	KeyboardMovingDown = false;
}

void AMainCharacter::AxisMoveLeftRight(float value)
{
	// Implement later
}
void AMainCharacter::AxisMoveUpDown(float value)
{
	// Implement later
}

void AMainCharacter::MouseLeftClick()
{
	FHitResult Hit;
	GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility), false, Hit);

	AActor* HitActor = Hit.GetActor();

	if (HitActor)
	{
		if (GameMode->IsInteractible(HitActor))
		{
			UInteractableObject* Component = GameMode->GetInteractor(HitActor);

			if (Component)
			{
				if (GetDistanceBetweenActors(HitActor, this) > 100)
				{
					UE_LOG(LogTemp, Warning, TEXT("Not close enough to activate, moving to it..."));
					DelayActivate = true;
					DelayActivateObject = Component;
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("Got interactor, sending activate command..."));
					Component->ActivateObject();
				}
			}
			else {
				UE_LOG(LogTemp, Warning, TEXT("Can't find interactor checking if it actually is a StaticMeshInteractor"));

				AInteractableStaticMeshObject* StaticMeshInteractor = GameMode->GetStaticMeshInteractor(HitActor);

				if (StaticMeshInteractor)
				{
					if (GetDistanceBetweenActors(HitActor, this) > 100)
					{
						UE_LOG(LogTemp, Warning, TEXT("Not close enough to pick up object, moving to it..."));
						DelayActivate = true;
						DelayActivateStaticMeshObject = StaticMeshInteractor;
					}
					else {
						UE_LOG(LogTemp, Warning, TEXT("Got StaticMeshInteractor, sending activate command..."));
						StaticMeshInteractor->ActivateObject(Cast<AActor>(this));
					}
				}
			}
		}

		MoveTo = Hit.ImpactPoint;
		MouseMove = true;
	}
}
void AMainCharacter::MouseRightClick()
{

}

void AMainCharacter::UpdateMovement()
{
	if (KeyboardMovingLeft)
	{
		AddMovementInput(FVector(1, 0, 0), 1.0f);
	}

	if (KeyboardMovingRight)
	{
		AddMovementInput(FVector(-1, 0, 0), 1.0f);
	}

	if (KeyboardMovingUp)
	{
		AddMovementInput(FVector(0, 1, 0), 1.0f);
	}

	if (KeyboardMovingDown)
	{
		AddMovementInput(FVector(0, -1, 0), 1.0f);
	}
}

void AMainCharacter::UpdateRotation()
{
	if (!SkeletalMeshComponent)
		return;

	if (KeyboardMovingLeft && !KeyboardMovingRight)
	{
		Rotation = FRotator(0, -90, 0);
	}

	if (KeyboardMovingRight && !KeyboardMovingLeft)
	{
		Rotation = FRotator(0, 90, 0);
	}

	if (KeyboardMovingUp && !KeyboardMovingDown)
	{
		Rotation = FRotator(0, 0, 0);
	}

	if (KeyboardMovingDown && !KeyboardMovingUp)
	{
		Rotation = FRotator(0, 180, 0);
	}

	if (KeyboardMovingLeft && KeyboardMovingUp)
	{
		Rotation = FRotator(0, -45, 0);
	}

	if (KeyboardMovingRight && KeyboardMovingUp)
	{
		Rotation = FRotator(0, 45, 0);
	}

	if (KeyboardMovingLeft && KeyboardMovingDown)
	{
		Rotation = FRotator(0, -135, 0);
	}

	if (KeyboardMovingRight && KeyboardMovingDown)
	{
		Rotation = FRotator(0, 135, 0);
	}

	SkeletalMeshComponent->SetWorldRotation(Rotation);
}

// Misc functions
float AMainCharacter::GetDistanceBetweenActors(AActor* Actor1, AActor* Actor2)
{
	return FVector::Dist(Actor1->GetActorLocation(), Actor2->GetActorLocation());
}

bool AMainCharacter::AddItemToInventory(InventoryItem* item)
{
	if (PlayerInventory)
		return PlayerInventory->AddItem(item);
	else
		return false;
}