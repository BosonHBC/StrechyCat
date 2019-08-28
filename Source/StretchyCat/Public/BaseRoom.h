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
	class UBoxComponent* RoomEntrance;
	UPROPERTY(BlueprintReadWrite, Category = "Info")
	TArray < class AObjectiveItemBase* > AllObjectives;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
	FName RoomName;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UBoxComponent* RoomExit;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UBoxComponent* RoomSpawn;
	// Sets default values for this actor's properties
	ABaseRoom();
	DECLARE_DELEGATE(RoomDelegate)
	DECLARE_DELEGATE_RetVal_OneParam(bool, CompleteObjectiveDelegate, int)

	RoomDelegate OnCompleteRoom;
	CompleteObjectiveDelegate OnCompleteObjective, OnUncompleteObjective;

	UPROPERTY(Replicated, BlueprintReadOnly , Category = "Info")
	int CurrentObjectiveCount;
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Info")
	int TotalObjectives;
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Info")
	bool IsRoomCompleted;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	virtual void EnterTheRoom(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void LeaveTheRoom(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual bool CompleteObjective(int objNum);
	virtual bool UncompleteObjective(int objNum);

	UFUNCTION(BlueprintImplementableEvent, Category = "Gameplay")
	void OnRoomComplete();

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	class AObjectiveItemBase * GetAnUncompleteObjective() const;
};
