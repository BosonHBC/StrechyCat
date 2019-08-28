// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "StretchyCatGameMode.h"
#include "StretchyCatPlayerController.h"
#include "StretchyCatCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "SCGameState.h"
#include "SCBaseController.h"
#include "SCCharacterBase.h"
#include "SCPlayerState.h"
#include "BaseRoom.h"
#include "Engine/World.h"
#include "Components/BoxComponent.h"
#include "EngineUtils.h"


void AStretchyCatGameMode::BeginPlay()
{
	CurrentSharedLife = MaxSharedLife;

}

void AStretchyCatGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	ASCPlayerState * playerState = Cast<ASCPlayerState>(NewPlayer->PlayerState);
	playerState->SetMaxLife(CurrentSharedLife);
	playerState->SetCurrentLife(MaxSharedLife);
	playerState->SetPlayerName(FString("Player") + FString::FromInt(GetNumPlayers()));
	UE_LOG(LogTemp, Warning, TEXT("PostLogin: %d"), playerState->GetMaxHealth());
}

AStretchyCatGameMode::AStretchyCatGameMode()
{
	//// use our custom PlayerController class
	PlayerControllerClass = AStretchyCatPlayerController::StaticClass();

	GameStateClass = ASCGameState::StaticClass();

	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	//if (PlayerPawnBPClass.Class != NULL)
	//{
	//	DefaultPawnClass = PlayerPawnBPClass.Class;
	//}
	MaxSharedLife = 4;
	CurrentSharedLife = MaxSharedLife;
}

void AStretchyCatGameMode::GetDamage(int _dmg)
{
	auto GS = GetGameState<ASCGameState>();
	CurrentSharedLife -= _dmg;
	GS->ChangeLifeCount(CurrentSharedLife, MaxSharedLife);
	if (CurrentSharedLife <= 0) {
		CurrentSharedLife = 0;
		GS->GameOver(true);
	}
}

void AStretchyCatGameMode::InitHealth()
{
	auto GS = GetGameState<ASCGameState>();
	GS->ChangeLifeCount(CurrentSharedLife, MaxSharedLife);
}


void AStretchyCatGameMode::SendServerMessageToUI(const FText& message)
{
	auto GS = GetGameState<ASCGameState>();

	GS->SendMessageToUI(message);
}

void AStretchyCatGameMode::CreateSelectedPawn_Implementation(TSubclassOf<ASCCharacterBase> selectedCharacter, ASCBaseController * playerController)
{
	auto oldPawn = playerController->GetPawn();

	auto newCharacter = GetWorld()->SpawnActor<ASCCharacterBase>(selectedCharacter, InitialRoom->RoomSpawn->GetComponentLocation(), FRotator(0.0f, 0.0f, 0.0f), FActorSpawnParameters());
	if (newCharacter != nullptr && oldPawn)
	{
		GetWorld()->DestroyActor(oldPawn);
		playerController->Possess(newCharacter);

	}
	else
		SendServerMessageToUI(FText::FromString(TEXT("Character cannot spawn at the moment.")));
}

//void AStretchyCatGameMode::DecGoalObjectiveCount(ABaseRoom* Room)
//{
//	ASCGameState * scGS = GetGameState<ASCGameState>();
//	scGS->SetGameObjective(scGS->GetCurrentObjective(), scGS->GetGoalObjective() - 1);
//}

