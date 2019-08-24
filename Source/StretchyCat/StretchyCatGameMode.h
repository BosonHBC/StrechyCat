// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "StretchyCatGameMode.generated.h"


UCLASS(minimalapi)
class AStretchyCatGameMode : public AGameModeBase
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
		int MaxSharedLife;
	UPROPERTY(VisibleAnywhere, Category = "Gameplay")
		int CurrentSharedLife;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		TSubclassOf<class ABaseRoom> InitialRoomClass;

	class ABaseRoom* InitialRoom;
public:
	AStretchyCatGameMode();

	void GetDamage(int _dmg);
	void InitHealth();

	void IncCurrentObjectiveCount(class ABaseRoom* Room);
	//void IncGoalObjectiveCount(ABaseRoom* Room);
	void DecCurrentObjectiveCount(class ABaseRoom* Room);
	//void DecGoalObjectiveCount(ABaseRoom* Room);
};



