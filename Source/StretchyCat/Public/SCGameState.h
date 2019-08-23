// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "SCGameState.generated.h"

/**
 * 
 */
UCLASS()
class STRETCHYCAT_API ASCGameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	ASCGameState();
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
		int MaxSharedLife;
	UPROPERTY(VisibleAnywhere, Category = "Gameplay")
		int CurrentSharedLife;
public:

	int GetCurrentLife() const { return CurrentSharedLife; }

	UFUNCTION(BlueprintImplementableEvent, Category = "GameLoop")
	void GameOver(bool _success);

	UFUNCTION(NetMulticast, Reliable)
	void ChangeLifeCount(int cur_health, int max_health);
};
