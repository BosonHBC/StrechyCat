// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SCInteractableBase.h"
#include "SCIPickable.generated.h"

/**
 *
 */
UCLASS()
class STRETCHYCAT_API ASCIPickable : public ASCInteractableBase
{
	GENERATED_BODY()

public:
	ASCIPickable();

protected:



	UPROPERTY(Replicated)
		class USceneComponent* PickPointSceneComp;
	UPROPERTY(Replicated)
		bool bHolding;

	void DoInteraction(class ASCCharacterBase* ownActor) override;

	void CancelInteraction() override;

private:
public:
	virtual void Tick(float DeltaTime) override;

	virtual void ServerDoInteraction_Implementation(class ASCCharacterBase* ownActor) override;
	virtual void ServerCancelInteraction_Implementation() override;

	virtual void MulticastDoInteraction_Implementation(class ASCCharacterBase* ownActor) override;
	virtual void MulticastCancelInteraction_Implementation() override; 
};
