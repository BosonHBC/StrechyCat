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
#include "StretchyCatGameMode.h"
#include "TimerManager.h"
#include "Components/SkeletalMeshComponent.h"
#include "Materials/Material.h"
#include "StretchyCatPlayerController.h"

// Sets default values
ASCCharacterBase::ASCCharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Configure character movement
	//GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a camera...

	FollowCameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCameraComp->SetupAttachment(CameraBoom); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCameraComp->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	InteractionPoint = CreateDefaultSubobject<USceneComponent>(TEXT("InteractPoint"));
	bInteracting = false;

	NormalMaterial = CreateDefaultSubobject<UMaterial>(TEXT("NormalMaterial"));
	InvinceMaterial = CreateDefaultSubobject<UMaterial>(TEXT("InvinceMaterial"));

	InvinceTime = 3.f;

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
	ServerUseAbility();
}
void ASCCharacterBase::UnUseAbility()
{
	ServerUnUseAbility();
}
void ASCCharacterBase::ServerUseAbility_Implementation()
{

}

bool ASCCharacterBase::ServerUseAbility_Validate()
{
	return true;
}

void ASCCharacterBase::ServerUnUseAbility_Implementation()
{

}

bool ASCCharacterBase::ServerUnUseAbility_Validate()
{
	return true;
}

void ASCCharacterBase::MoveForward(float _value)
{
	AddMovementInput(GetActorForwardVector() * _value);

}

void ASCCharacterBase::MoveRight(float _value)
{
	AddMovementInput(GetActorRightVector() * _value);

}

void ASCCharacterBase::Jump()
{
	// parent character Jump function;
	Super::Jump();
}

void ASCCharacterBase::TakeDamage(AActor* DmgFrom, int _dmg)
{
	if (Role == ROLE_Authority)
	{
		AStretchyCatGameMode * scGM = GetWorld()->GetAuthGameMode<AStretchyCatGameMode>();
		//scGM->GetDamage(_dmg);
	}
	StartInvincible(DmgFrom);
	OnTakeDamage(DmgFrom);
}


void ASCCharacterBase::Respawn(FVector GroundLocation)
{
	// Respawn the player in another player's head
	
	SetActorLocationAndRotation(GroundLocation + FVector(0, 0, 400.f), FRotator::ZeroRotator, false);
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

}

void ASCCharacterBase::OnInvinceTimeOver()
{
	bInvincible = false;
	GetMesh()->SetMaterial(0, NormalMaterial);
	EnableInput(nullptr);

	// Temp Position
	Respawn(FVector(0, 0, 170.f));
}

void ASCCharacterBase::StartInvincible(AActor* DmgFrom)
{
	DisableInput(nullptr);
	// Start Timer
	GetWorldTimerManager().SetTimer(InvinceTimeHandle, this,&ASCCharacterBase::OnInvinceTimeOver, InvinceTime, false);
	bInvincible = true;
	// Change Material
	GetMesh()->SetMaterial(0, InvinceMaterial);
	//Set Knock back
	FVector DmgImpulse = ((GetActorLocation() - DmgFrom->GetActorLocation()).GetSafeNormal() - GetActorForwardVector())* DmgFrom->GetVelocity().Size() * 20.f;
	GetCharacterMovement()->AddImpulse(DmgImpulse);
}

// Called every frame
void ASCCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DrawDebugSphere(GetWorld(), InteractionPoint->GetComponentLocation(), 16, 8, FColor::Orange, false);

	FHitResult OutHit;
	FVector Start = InteractionPoint->GetComponentLocation();
	FVector Direction = InteractionPoint->GetForwardVector();

	GetWorld()->LineTraceSingleByChannel(OutHit, Start, Start + Direction * 80.f, ECC_Visibility, CollisionParams);
	AActor* HitActor = OutHit.GetActor();
	if (HitActor != nullptr) {
		DrawDebugLine(GetWorld(), Start, HitActor->GetActorLocation(), FColor::Blue, true);
		ASCInteractableBase* baseInteractable = Cast<ASCInteractableBase>(HitActor);
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

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ASCCharacterBase::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ASCCharacterBase::LookUpAtRate);

	PlayerInputComponent->BindAction("Ability", IE_Pressed, this, &ASCCharacterBase::UseAbility);
	PlayerInputComponent->BindAction("Ability", IE_Released, this, &ASCCharacterBase::UnUseAbility);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASCCharacterBase::Jump);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ASCCharacterBase::Interact);
}

void ASCCharacterBase::TurnAtRate(float _value)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(_value * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ASCCharacterBase::LookUpAtRate(float _value)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(_value * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

