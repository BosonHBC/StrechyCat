// Fill out your copyright notice in the Description page of Project Settings.

#include "SCCharacterBase.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "StretchyCatPlayerController.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "SCGameState.h"
#include "Components/SceneComponent.h"
#include "SCInteractableBase.h"

// Sets default values
ASCCharacterBase::ASCCharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = true;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->RelativeRotation = FRotator(-60.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	InteractionPoint = CreateDefaultSubobject<USceneComponent>(TEXT("InteractPoint"));
	bInteracting = false;
	SetReplicates(true);
	SetReplicateMovement(true);
}

// Called when the game starts or when spawned
void ASCCharacterBase::BeginPlay()
{
	Super::BeginPlay();

}

void ASCCharacterBase::UseAbility()
{
	// Base Ability

}

void ASCCharacterBase::UnUseAbility()
{
	// Base release ability

}

void ASCCharacterBase::MoveForward(float _value)
{
	AddMovementInput(FVector::ForwardVector * _value);

}

void ASCCharacterBase::MoveRight(float _value)
{
	AddMovementInput(FVector::RightVector * _value);

}

void ASCCharacterBase::Jump()
{
	// parent character Jump function;
	Super::Jump();
}

void ASCCharacterBase::TakeDamage(int _dmg)
{
	ASCGameState* scGS = GetWorld()->GetGameState<ASCGameState>();
	scGS->GetDamage(_dmg);
}


void ASCCharacterBase::Interact()
{
	// Base Interact
	if (!bInteracting && InteractingActor != nullptr) {
		bInteracting = true;
		InteractingActor->DoInteraction(this);
	}
	else if (bInteracting && InteractingActor != nullptr) {
		bInteracting = false;
		InteractingActor->CancelInteraction();
	}

	//DrawDebugLine(GetWorld(), InteractionPoint->GetComponentLocation(), InteractionPoint->GetComponentLocation() + InteractionPoint->GetForwardVector() * 80.f, FColor::Blue, true);
}

// Called every frame
void ASCCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	FHitResult OutHit;
	FVector Start = InteractionPoint->GetComponentLocation();
	FVector Direction = InteractionPoint->GetForwardVector();
	FCollisionQueryParams CollisionParams;

	if (GetWorld()->LineTraceSingleByChannel(OutHit, Start, Start + Direction * 80.f, ECC_Visibility, CollisionParams)) {
		DrawDebugLine(GetWorld(), Start, OutHit.GetActor()->GetActorLocation(), FColor::Blue, true);

		ASCInteractableBase* baseInteractable = Cast<ASCInteractableBase>(OutHit.GetActor());
		if (baseInteractable != nullptr) {
			InteractingActor = baseInteractable;
		}
	}
	else {
		if (!bInteracting)
			InteractingActor = nullptr;
	}
}

// Called to bind functionality to input
void ASCCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// SetupInput
	PlayerInputComponent->BindAxis("MoveForward", this, &ASCCharacterBase::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASCCharacterBase::MoveRight);

	PlayerInputComponent->BindAction("Ability", IE_Pressed, this, &ASCCharacterBase::UseAbility);
	PlayerInputComponent->BindAction("Ability", IE_Released, this, &ASCCharacterBase::UnUseAbility);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASCCharacterBase::Jump);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ASCCharacterBase::Interact);
}

