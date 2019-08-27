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

	UPROPERTY(Replicated, VisibleAnywhere, Category = "PlayerInfo")
	int CurrentHealth;
	UPROPERTY(Replicated, VisibleAnywhere, Category = "PlayerInfo")
	int MaxHealth;

protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const override;
public:
	
	void SetCurrentLife(int _lives);
	void SetMaxLife(int _lives);
	UPROPERTY(Replicated, VisibleAnywhere, Category = "PlayerInfo")
	class ABaseRoom* CurrentRoom;
	UFUNCTION(Client, Reliable, Category = "PlayerInfo")
		void SetCurrentRoom(class ABaseRoom* room, int currentObj, int totalObj);
	UFUNCTION(BlueprintCallable)
	int GetCurrentHealth() const;

	UFUNCTION(BlueprintCallable)
	int GetMaxHealth() const;

	UFUNCTION(BlueprintCallable)
	class ABaseRoom * GetCurrentRoom() const;
};
