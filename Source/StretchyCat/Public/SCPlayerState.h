// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SCPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class STRETCHYCAT_API ASCPlayerState : public APlayerState
{
	GENERATED_BODY()

	
protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const override;
public:
	
	UPROPERTY(Replicated, BlueprintReadWrite, Category = "PlayerInfo")
		int CurrentHealth;
	UPROPERTY(Replicated, BlueprintReadWrite, Category = "PlayerInfo")
		int MaxHealth;
	UPROPERTY(Replicated, BlueprintReadWrite, Category = "PlayerInfo")
		int CurrentObjective;
	UPROPERTY(Replicated, BlueprintReadWrite, Category = "PlayerInfo")
		int TotalObjective;
	UPROPERTY(Replicated, BlueprintReadWrite, Category = "PlayerInfo")
		FName CurrentRoomName;
};
