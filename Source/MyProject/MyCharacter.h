// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class MYPROJECT_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	void SetLife(int NewLife);
	int GetLife();

	void SetColeta(int NewColeta);
	int GetColeta();

	FORCEINLINE int GetNewLine() const { return Life; }
	FORCEINLINE void AMyCharacter::GetNewLine(int NewLine) { Life = NewLine; }
	FORCEINLINE TArray<class AItem*>GetInventory() const { return Inventory; }

	void OnDeath();
	void ColorirCubo();
	void DescolorirCubo();
	
	
	
	
private: 
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere)
		UCameraComponent* PlayerCamera;

	UPROPERTY(EditAnywhere)
		USpringArmComponent* CameraBoom;
	UPROPERTY(EditAnywhere)
	int Life = 3;

	UPROPERTY(EditAnywhere)
		int Coleta = 0;



	UPROPERTY(EditAnywhere)
		UArrowComponent* ArrowComp;

	UPROPERTY(EditAnywhere)
		int Cubo = 0;

	USphereComponent* CollectCollisionComp;
	TArray<class AItem*> Inventory;
	TSubclassOf<class UUserWidget> UserWidget;

	void MoveForward(float value);
	void MoveRight(float Value);
	void StartRun();
	void StopRun();
	void DropProjectile();
	void Turn(float Value);
	void OnCollect();
	void Pause();



	UPROPERTY(EditAnywhere)
		float DamageAmount = -1;

	//OnHit
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			FVector NormalImpulse, const FHitResult & Hit);


	
};
