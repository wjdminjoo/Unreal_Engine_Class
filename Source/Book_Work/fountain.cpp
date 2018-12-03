// Fill out your copyright notice in the Description page of Project Settings.

#include "fountain.h"


// Sets default values
Afountain::Afountain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	
	body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BODY"));
	water =  CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WATER"));
	light = CreateDefaultSubobject<UPointLightComponent>(TEXT("LIGHT"));
	splash = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SPLASH"));
	Movement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("MOVEMENT"));
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("PROJECTILE"));

	RootComponent = body;
	water->SetupAttachment(body);
	light->SetupAttachment(body);
	splash->SetupAttachment(body);


	water->SetRelativeLocation(FVector(0.0f, 0.0f, 135.0f));
	light->SetRelativeLocation(FVector(0.0f, 0.0f, 195.0f));
	splash->SetRelativeLocation(FVector(0.0f, 0.0f, 195.0f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_BODY(TEXT("/Game/InfinityBladeGrassLands/Environments/Plains/Env_Plains_Ruins/StaticMesh/SM_Plains_Castle_Fountain_01.SM_Plains_Castle_Fountain_01"));
	if (SM_BODY.Succeeded()) body->SetStaticMesh(SM_BODY.Object);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_WATER(TEXT("M/Game/InfinityBladeGrassLands/Effects/FX_Materials/Liquid/M_Water_fountain_01.M_Water_fountain_01"));
	if (SM_WATER.Succeeded()) body->SetStaticMesh(SM_WATER.Object);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_SPLASH(TEXT("/Game/InfinityBladeGrassLands/Effects/FX_Ambient/Water/P_Water_Fountain_Splash_Base_01.P_Water_Fountain_Splash_Base_01"));
	if (SM_SPLASH.Succeeded()) body->SetStaticMesh(SM_SPLASH.Object);

	//Movement->RotationRate = FRotator(0.0f, RotateSpeed, 0.0f); // 자동차의 엔진같은 역할. 
	ProjectileMovement->InitialSpeed = 4000.0f;
	ProjectileMovement->bShouldBounce = true;

}

// Called when the game starts or when spawned
void Afountain::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogClass, Warning, TEXT("I WNANA GO HOME"));
	// FString은 포인터를 이용해 불러와야한다.
	UE_LOG(Book_Work, Warning, TEXT("ACTOR NAME :  %s, ID : %d, Location X : %.3f"), *GetName(), ID, GetActorLocation().X);
	

	ABLOG_S(Warning);
	ABLOG(Warning, TEXT("ACTOR NAME :  %s, ID : %d, Location X : %.3f"), *GetName(), ID, GetActorLocation().X);
	ABLOG(Warning, TEXT("TYPE NAME :  %s, ID : %d, Location X : %.3f"), *GetClass()->GetName(), ID, GetActorLocation().X);
	ABLOG(Warning, TEXT("TYPE NAME :  %s, ID : %d, Location X : %.3f"), *Afountain::StaticClass()->GetName(), ID, GetActorLocation().X);

}

void Afountain::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ABLOG_S(Warning);

}

void Afountain::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	ABLOG_S(Warning);
}

// Called every frame
void Afountain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalRotation(FRotator(0, RotateSpeed * DeltaTime, 0));
}

