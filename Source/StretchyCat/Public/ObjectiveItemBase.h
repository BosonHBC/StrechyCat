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
public:	
	// Sets default values for this actor's properties
	AObjectiveItemBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//for inheritance
	virtual void Internal_CompleteObjective(class ASCBaseController* playerController);
	virtual void Internal_UncompleteObjective(class ASCBaseController* playerController);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Objective")
	void CompleteObjective(class ASCBaseController * playerController);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Objective")
	void UncompleteObjective(class ASCBaseController* playerController);
};
