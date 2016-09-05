// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject.h"
#include "Caixa.h"
#include "Projectile.h"



// Sets default values
ACaixa::ACaixa()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	Root = CreateDefaultSubobject<UBoxComponent >(TEXT("Root"));
	Root->bGenerateOverlapEvents = true;
	Root->SetCollisionProfileName("OverlapAllDynamic");
	
	RootComponent = Root;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionProfileName("NoColision");
	MeshComp->AttachTo(RootComponent);

}

// Called when the game starts or when spawned
void ACaixa::BeginPlay()
{
	Super::BeginPlay();
	
}



void ACaixa::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	RunningTime += DeltaTime;
	float ShootTime = 1.0f * RunningTime;

	if (ShootTime > 2.0f) {
		FActorSpawnParameters SpawnParameters;
		UWorld* World = GetWorld();
		if (World != nullptr) {
			FRotator Rotation = MeshComp->GetComponentRotation();
			AProjectile* Proj = World->SpawnActor<AProjectile>
				(GetActorLocation(), Rotation,
					SpawnParameters);
			if (Proj != nullptr) {
				RunningTime = 0.0f;
			}
		}
	}
}


void ACaixa::DropProjectile() {
	FActorSpawnParameters SpawnParameters;
	UWorld* World = GetWorld();

	if (World != nullptr) {
		FRotator Rotation = MeshComp->GetComponentRotation();
		AProjectile* Proj = World->SpawnActor<AProjectile>
			(GetActorLocation(), Rotation, SpawnParameters);
		if (Proj != nullptr) {
			UE_LOG(LogTemp, Warning, TEXT("Spawn OK!"));
		}
	}

}








