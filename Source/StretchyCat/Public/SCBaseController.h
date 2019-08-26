// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SCBaseController.generated.h"

/**
 * 
 */
UCLASS()
class STRETCHYCAT_API ASCBaseController : public APlayerController
{
	GENERATED_BODY()

public:
	ASCBaseController();
	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = "CharacterSelect")
	void SelectCharacterClass(TSubclassOf<class ASCCharacterBase> selectedClass);

	UFUNCTION(BlueprintImplementableEvent, Category = "UIShowMessage")
	void ShowServerMessage(const FText & message);
};
