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
	UPROPERTY(Replicated, VisibleAnywhere, Category = "PlayerInfo")
		int CurrentHealth;
	UPROPERTY(Replicated, VisibleAnywhere, Category = "PlayerInfo")
		int MaxHealth;
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "PlayerInfo")
		int CurrentObjective;
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "PlayerInfo")
		int TotalObjective;
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "PlayerInfo")
		FName RoomNamePlayerIn;
	void SetCurrentLife(int _lives);
	void SetMaxLife(int _lives);
	UFUNCTION(Client, Reliable, Category = "PlayerInfo")
	void SetCurrentRoomObj(const FName& roomName, int currentObj, int totalObj);
	UFUNCTION(BlueprintCallable)
	int GetCurrentHealth() const;
	UFUNCTION(BlueprintCallable)
	int GetMaxHealth() const;
	UFUNCTION(BlueprintCallable)
		int GetCurrentObjective()const { return CurrentObjective; }
	UFUNCTION(BlueprintCallable)
		int GetTotalObjective()const { return TotalObjective; }
	UFUNCTION(BlueprintCallable)
		FName GetCurrentRoomName()const { return RoomNamePlayerIn; }
};
