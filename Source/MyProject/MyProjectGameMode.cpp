// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject.h"
#include "MyProjectGameMode.h"
#include "MyHUD.h"
#include "MyCharacter.h"

AMyProjectGameMode::AMyProjectGameMode() {

	//HUDClass = AMyHUD::StaticClass();

	DefaultPawnClass = AMyCharacter::StaticClass();

}


