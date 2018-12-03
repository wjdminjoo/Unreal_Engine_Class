// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Book_Work.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "EngineMinimal.h"
#include "GameFramework/Actor.h"
#include "fountain.generated.h" // TYPE 객체가 들어가있다. CDO라고 부른다. CLASS DEFAULT OBJECT.
UCLASS()
class BOOK_WORK_API Afountain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Afountain();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override; // START
	virtual void PostInitializeComponents() override; // AWAKE
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override; // Update

	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* body;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* water;
	UPROPERTY(VisibleAnywhere)
	UPointLightComponent* light;
	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* splash;
	UPROPERTY(VisibleAnywhere)
		int32 ID;
	UPROPERTY(VisibleAnywhere)
		URotatingMovementComponent* Movement;
	UPROPERTY(VisibleAnywhere)
		UProjectileMovementComponent* ProjectileMovement;

private:
	UPROPERTY(EditAnyWhere)
	float RotateSpeed;
	
};
