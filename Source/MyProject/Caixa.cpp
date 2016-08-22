// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject.h"
#include "Caixa.h"


// Sets default values
ACaixa::ACaixa()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACaixa::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACaixa::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

