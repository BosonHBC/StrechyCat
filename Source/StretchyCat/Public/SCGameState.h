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
	/*UPROPERTY(Replicated, BlueprintReadOnly, Category = "Gameplay")
		int ObjectiveGoal;
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Gameplay")
		int CurrentObjective;

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;*/
public:

	/*UFUNCTION(BlueprintCallable, Category = "GameObjective")
	int GetCurrentObjective() const { return CurrentObjective; }
	UFUNCTION(BlueprintCallable, Category = "GameObjective")
	int GetGoalObjective() const { return ObjectiveGoal; }*/

	UFUNCTION(BlueprintNativeEvent, Category = "GameLoop")
	void GameOver(bool _success);

	UFUNCTION(NetMulticast, Reliable)
	void ChangeLifeCount(int cur_health, int max_health);

	UFUNCTION(NetMulticast, Reliable)
	void SendMessageToUI(const FText & message);

	//objNum < 0 means uncomplete
	UFUNCTION(NetMulticast, Reliable)
	void PlayerCompleteObjective(class ABaseRoom * room, int objNum);
};
