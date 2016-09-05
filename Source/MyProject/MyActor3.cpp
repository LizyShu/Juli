// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject.h"
#include "MyActor3.h"


// Sets default values
AMyActor3::AMyActor3()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	RootComponent = Root;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->AttachTo(RootComponent);

}

// Called when the game starts or when spawned
void AMyActor3::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyActor3::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );


	FVector LocalizacaoAtual = GetActorLocation();
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	LocalizacaoAtual.Z += DeltaHeight * 500;
	RunningTime += DeltaTime;
	SetActorLocation(LocalizacaoAtual);

}



