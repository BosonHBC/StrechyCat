// Fill out your copyright notice in the Description page of Project Settings.

#include "SCCharacterBase.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ASCCharacterBase::ASCCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

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

	

}

// Called when the game starts or when spawned
void ASCCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
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

// Called every frame
void ASCCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASCCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// SetupInput
	PlayerInputComponent->BindAxis("MoveForward", this, &ASCCharacterBase::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASCCharacterBase::MoveRight);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASCCharacterBase::Jump);
}

