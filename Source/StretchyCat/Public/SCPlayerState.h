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
	UPROPERTY(Replicated, VisibleAnywhere, Category = "PlayerInfo")
	class ABaseRoom* CurrentRoom;
protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const override;
public:
	
	void SetCurrentLife(int _lives);
	void SetMaxLife(int _lives);
	UFUNCTION(Server, Reliable, WithValidation, Category = "PlayerInfo")
	void SetCurrentRoom(class ABaseRoom* room);
	UFUNCTION(BlueprintCallable)
	int GetCurrentHealth() const;

	UFUNCTION(BlueprintCallable)
	int GetMaxHealth() const;

	UFUNCTION(BlueprintCallable)
	class ABaseRoom * GetCurrentRoom() const;
};
