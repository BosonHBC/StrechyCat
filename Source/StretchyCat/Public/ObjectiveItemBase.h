// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjectiveItemBase.generated.h"

UCLASS()
class STRETCHYCAT_API AObjectiveItemBase : public AActor
{
	GENERATED_BODY()

	UPROPERTY(Replicated, VisibleAnywhere, Category = "Objective")
	bool isCompleted;

	UPROPERTY(Replicated, VisibleAnywhere, Category = "Objective")
	class ASCBaseController * CompletedPlayer;
public:	
	// Sets default values for this actor's properties
	AObjectiveItemBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame                          
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleAnywhere, Category = "Room")
	class ABaseRoom * RoomAttached;
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable, Server, Reliable, WithValidation, Category = "Objective")
	void CompleteObjective(class ASCBaseController * playerController);
	UFUNCTION(BlueprintCallable, Server, Reliable, WithValidation, Category = "Objective")
	void UncompleteObjective(class ASCBaseController* playerController);
	UFUNCTION(BlueprintCallable, Category = "Objective")
	bool GetIfCompleted() const { return isCompleted; }

};
