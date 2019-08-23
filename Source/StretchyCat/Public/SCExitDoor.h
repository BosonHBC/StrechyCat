// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SCExitDoor.generated.h"

UCLASS()
class STRETCHYCAT_API ASCExitDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASCExitDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category= "Components")
	UStaticMeshComponent * DoorMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UBoxComponent * ActivateArea;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor * OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor * OtherActor) override;

};
