// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SCInteractableBase.generated.h"

UCLASS()
class STRETCHYCAT_API ASCInteractableBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASCInteractableBase();
	UPROPERTY(VisibleAnywhere, Category = "Componetns")
		class UStaticMeshComponent* SuperMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void DoInteraction(class ASCCharacterBase* ownActor );

	virtual void CancelInteraction();

	UFUNCTION(Server, Reliable, WithValidation)
	virtual void ServerDoInteraction(class ASCCharacterBase* ownActor);
	UFUNCTION(Server, Reliable, WithValidation)
	virtual void ServerCancelInteraction();
};
