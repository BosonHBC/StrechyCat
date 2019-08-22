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
		uint16 MaxSharedLife;
	UPROPERTY(VisibleAnywhere, Category = "Gameplay")
		uint16 CurrentSharedLife;
public:

	int GetCurrentLife() const { return CurrentSharedLife; }

	void GetDamage(uint16 _dmg);

	UFUNCTION(BlueprintImplementableEvent, Category = "GameLoop")
	void GameOver(bool _success);
};
