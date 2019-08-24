// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseRoom.generated.h"

UCLASS()
class STRETCHYCAT_API ABaseRoom : public AActor
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* RoomFloor;
	UPROPERTY(Replicated, VisibleAnywhere, Category = "Components")
	TArray < class AObjectiveItemBase* > AllObjectives;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
	FName RoomName;
	// Sets default values for this actor's properties
	ABaseRoom();
	DECLARE_DELEGATE(RoomDelegate)
	DECLARE_DELEGATE_RetVal_OneParam(bool, CompleteObjectiveDelegate, int)

	RoomDelegate OnEnterRoom, OnLeaveRoom, OnCompleteRoom;
	CompleteObjectiveDelegate OnCompleteObjective, OnUncompleteObjective;

	UPROPERTY(Replicated, BlueprintReadOnly , Category = "Info")
	int CurrentObjectiveCount;
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Info")
	int TotalObjectives;
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Info")
	bool IsRoomCompleted;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
	FVector PlayerSpawnLocation;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	virtual void EnterTheRoom();
	UFUNCTION()
	virtual void LeaveTheRoom();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Gameplay")
	void OnRoomComplete();
};
