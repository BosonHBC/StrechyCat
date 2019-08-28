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

	void CompleteObjective(class ABaseRoom* room);
	void UncompleteObjective(class ABaseRoom* room);
	void EnterTheRoom(const FName & roomName, int curObj, int totalObj);
	UFUNCTION(BlueprintImplementableEvent, Category = "CharacterStatus")
	void OnPlayerEnterRoom();
	UFUNCTION(BlueprintImplementableEvent, Category = "UIShowMessage")
	void ShowServerMessage(const FText & message);
};
