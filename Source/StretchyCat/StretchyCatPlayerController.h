// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "StretchyCatPlayerController.generated.h"

UCLASS()
class AStretchyCatPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AStretchyCatPlayerController();

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

};


