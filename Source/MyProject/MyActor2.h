// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "MyActor2.generated.h"

UCLASS()
class MYPROJECT_API AMyActor2 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor2();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
private:

	UPROPERTY(EditAnywhere)
		UShapeComponent* Root;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, Category = Tick)
		float RunningTime = 0;
	UPROPERTY(VisibleAnywhere, Category = Tick)
		float RunningTime1 = 10;
	UPROPERTY(VisibleAnywhere, Category = Tick)
		float RunningTime2 = 20;
	UPROPERTY(VisibleAnywhere, Category = Tick)
		float RunningTime3 = 30;
	

	UPROPERTY(EditAnywhere)
		float DamageAmount = -1;
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	

	
};
