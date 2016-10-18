// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject.h"
#include "MyCharacter.h"
#include "ProjectTileActor.h"
#include "Item.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/UMGStyle.h"
#include "Runtime/UMG/Public/IUMGModule.h"
#include "Runtime/UMG/Public/Slate/SObjectWidget.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/UserWidget.h"



// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->bGenerateOverlapEvents = true;

	//MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	//MeshComp->SetCollisionProfileName("NoColission");
	//MeshComp->AttachTo(GetCapsuleComponent());

	ConstructorHelpers::FObjectFinder<USkeletalMesh>SkeletalMesh(TEXT("SkeletalMesh'/Game/AnimStarterPack/UE4_Mannequin/Mesh/SK_Mannequin.SK_Mannequin'"));
	if (SkeletalMesh.Succeeded()) {
		GetMesh()->SetSkeletalMesh(SkeletalMesh.Object);
	}
	GetMesh()->SetWorldLocation(FVector(-50.0f, 0.0f, 0.0f));
	GetMesh()->SetWorldScale3D(FVector(0.9f, 0.9f, 0.9f));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	ConstructorHelpers::FObjectFinder<UAnimBlueprint>AnimeObj(TEXT("AnimBlueprint'/Game/Blueprints/Walking.Walking'"));
	if (AnimeObj.Succeeded()) {
		GetMesh()->SetAnimInstanceClass(AnimeObj.Object->GetAnimBlueprintGeneratedClass());
	}

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	CameraBoom = CreateAbstractDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	PlayerCamera->AttachTo(CameraBoom);

	ArrowComp = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	ArrowComp->SetHiddenInGame(false);
	ArrowComp->ArrowSize = 2.0f;
	ArrowComp->AttachTo(GetMesh());

	CollectCollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollectCollisionComp"));
	CollectCollisionComp->InitSphereRadius(200.0f);
	CollectCollisionComp->AttachTo(RootComponent);

	GetCharacterMovement()->MaxWalkSpeed = 400;

	ConstructorHelpers::FClassFinder<UUserWidget>Widget(TEXT("WidgetBlueprint'/Game/Blueprints/Pause.Pause_C'"));
	if (Widget.Succeeded()) {
		UserWidget = Widget.Class;
	}

	//AutoPossessPlayer = EAutoReceiveInput::Player0;

}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);

	InputComponent->BindAxis("Turn", this, &AMyCharacter::Turn);


	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	InputComponent->BindAction("Run", IE_Pressed, this, &AMyCharacter::StartRun);
	InputComponent->BindAction("Run", IE_Released, this, &AMyCharacter::StopRun);
	InputComponent->BindAction("Drop", IE_Pressed, this, &AMyCharacter::DropProjectile);
	InputComponent->BindAction("Collect", IE_Pressed, this, &AMyCharacter::OnCollect);

	InputComponent->BindAction("Pause", IE_Pressed, this, &AMyCharacter::Pause);
	 


}

void AMyCharacter::MoveForward(float value) {

	FVector Forward(1, 0, 0);
	AddMovementInput(Forward, value);




}
void AMyCharacter::MoveRight(float value) {

	FVector Right(0, 1, 0);
	AddMovementInput(Right, value);




}


void AMyCharacter::StartRun() {
	GetCharacterMovement()->MaxWalkSpeed = 10500;

}
void AMyCharacter::StopRun() {
	GetCharacterMovement()->MaxWalkSpeed = 10000;

}

void AMyCharacter::SetLife(int NewLife) {
	Life = NewLife;

}
int AMyCharacter::GetLife() {
	return Life;
}

void AMyCharacter::SetColeta(int NewColeta) {
	Coleta = NewColeta;
}

int AMyCharacter::GetColeta() {
	return Coleta;
}


void AMyCharacter::OnDeath() {
	if (Life <= 0) {
		FVector InitialLocation(-1300.0f, -90.0f, 68.0f);
		Life = 3;
		SetActorLocation(InitialLocation);
		UE_LOG(LogTemp, Warning, TEXT("O Personajem morreu!"))
	}
}

//OnHit.
void AMyCharacter::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult & Hit) {
	if (OtherActor && (OtherActor != this) && OtherComp) {

		UE_LOG(LogTemp, Warning, TEXT("OnHit"));
		AMyCharacter* MyCharacter = Cast<AMyCharacter>(OtherActor);
		MyCharacter->SetLife(MyCharacter->GetLife() + DamageAmount);
		MyCharacter->OnDeath();
		UE_LOG(LogTemp, Warning, TEXT("Life = %d"), MyCharacter->GetLife());
		Destroy();
	}
}




//LogVictoria

void AMyCharacter::ColorirCubo() {

	if ( Cubo == 6) {
		Cubo = Cubo + 1;
		UE_LOG(LogTemp, Warning, TEXT("Vitoria!"));
	}


}

void AMyCharacter::DescolorirCubo() {

	Cubo = Cubo - 1;

}



void AMyCharacter::DropProjectile() {
	FActorSpawnParameters SpawnParameters;
	UWorld* World = GetWorld();

	if (World != nullptr) {
		FRotator Rotation = GetMesh()->GetComponentRotation();
		AProjectTileActor* Proj = World->SpawnActor<AProjectTileActor>
			(GetActorLocation(), Rotation, SpawnParameters);
		if (Proj != nullptr) {
			UE_LOG(LogTemp, Warning, TEXT("Spawn OK!"));
		}
	}

}


void AMyCharacter::Turn(float Value) {

	//AddControllerYawInput(Value);
	FRotator NewRotation = GetMesh()->GetComponentRotation();
	NewRotation.Yaw += Value;
	GetMesh()->SetWorldRotation(NewRotation);



}

void AMyCharacter::OnCollect() {
	TArray<AActor*>AtoresColetados;
	CollectCollisionComp->GetOverlappingActors(AtoresColetados);

	for (int i = 0.; i < AtoresColetados.Num(); i++) {
		if (AtoresColetados[i]->IsA(AItem::StaticClass())) {
			AItem* ItemCoeltado = Cast<AItem>(AtoresColetados[i]);
			Inventory.Add(ItemCoeltado);
			ItemCoeltado->Destroy();
			UE_LOG(LogTemp, Warning, TEXT("%d"), Inventory.Num());
		}
	}

	
}

void AMyCharacter::Pause() {

	UWorld* World = GetWorld();
	if (World != nullptr) {
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(World, 0);
		if (PlayerController != nullptr && UserWidget != NULL) {
			PlayerController->SetPause(true);
			UUserWidget* UserW = UWidgetBlueprintLibrary::Create(World, UserWidget, PlayerController);
			if (UserW != nullptr) {
				UserW->AddToViewport();
				PlayerController->bShowMouseCursor = true;
			}
		}

	}
}


