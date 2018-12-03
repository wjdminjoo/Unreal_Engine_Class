// Fill out your copyright notice in the Description page of Project Settings.

#include "ABCharacter.h"


// Sets default values
AABCharacter::AABCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	SpringArm->TargetArmLength = 900.0f;
	SpringArm->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_DRAGON(TEXT("/Game/DesertDragon/Meshes/SK_DesertDragon.SK_DesertDragon"));
	if (SK_DRAGON.Succeeded()) GetMesh()->SetSkeletalMesh(SK_DRAGON.Object);
	
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	static ConstructorHelpers::FClassFinder<USkeletalMesh> DRAGON_ANIM(TEXT("/Game/DesertDragon/Animations/BPDesertDragon.BPDesertDragon_C"));
	if (DRAGON_ANIM.Succeeded()) GetMesh()->SetAnimInstanceClass(DRAGON_ANIM.Class);


	ArmLengthSpeed = 3.0f;
	ArmRotationSpeed = 10.0f;

	SetControlMode(EControlMode::GTA);
}

// Called when the game starts or when spawned
void AABCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void AABCharacter::SetControlMode(EControlMode NewControlMode)
{
	CurrentControlMode = NewControlMode;

	switch (CurrentControlMode) {
	case EControlMode::GTA:
		ArmLengthTo = 1800.0f;
		Camera->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
		SpringArm->bUsePawnControlRotation = true;
		SpringArm->bInheritPitch = true;
		SpringArm->bInheritRoll = true;
		SpringArm->bInheritYaw = true;
		SpringArm->bDoCollisionTest = true;
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->bUseControllerDesiredRotation = false;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
		break;

	case EControlMode::DIABLO:
		ArmLengthTo = 3200.0f;
		ArmRotationTo = FRotator(-45.0f, 0.0f, 0.0f);
		SpringArm->bUsePawnControlRotation = false;
		SpringArm->bInheritPitch = false;
		SpringArm->bInheritRoll = false;
		SpringArm->bInheritYaw = false;
		SpringArm->bDoCollisionTest = false;
		bUseControllerRotationYaw = true;
		GetCharacterMovement()->bOrientRotationToMovement = false;
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
		break;

	case EControlMode::SIDE:
		ArmLengthTo = 1000.0f;
		ArmRotationTo = FRotator(0.0f, 0.0f, 0.0f);
		SpringArm->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
		SpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		Camera->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
		Camera->SetRelativeLocation(FVector(800.0f, 1100.0f, 0.0f));
		SpringArm->bUsePawnControlRotation = true;
		SpringArm->bInheritPitch = false;
		SpringArm->bInheritRoll = false;
		SpringArm->bInheritYaw = true;
		SpringArm->bDoCollisionTest = false;
		bUseControllerRotationYaw = true;
		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
		break;

	case EControlMode::TOP:
		ArmLengthTo = 0.0f;
		ArmRotationTo = FRotator(0.0f, 0.0f, 0.0f);
		SpringArm->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
		SpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 2000.0f));
		Camera->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));
		Camera->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		SpringArm->bUsePawnControlRotation = true;
		SpringArm->bInheritPitch = false;
		SpringArm->bInheritRoll = false;
		SpringArm->bInheritYaw = false;
		SpringArm->bDoCollisionTest = false;
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
		break;

	case EControlMode::SHOULDER:
		ArmLengthTo = 500.0f;
		ArmRotationTo = FRotator(0.0f, 0.0f, 0.0f);
		SpringArm->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));
		SpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		Camera->SetRelativeRotation(FRotator(-20.0f, 0.0f, 0.0f));
		Camera->SetRelativeLocation(FVector(-500.0f, 400.0f, 500.0f));
		SpringArm->bUsePawnControlRotation = true;
		SpringArm->bInheritPitch = true;
		SpringArm->bInheritRoll = true;
		SpringArm->bInheritYaw = true;
		SpringArm->bDoCollisionTest = false;
		bUseControllerRotationYaw = true;
		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
		break;

	case EControlMode::FIRST:
		ArmLengthTo = -450.0f;
		ArmRotationTo = FRotator(0.0f, 0.0f, 0.0f);
		SpringArm->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
		SpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		Camera->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
		Camera->SetRelativeLocation(FVector(0.0f, 0.0f, 200.0f));
		SpringArm->bUsePawnControlRotation = true;
		SpringArm->bInheritPitch = true;
		SpringArm->bInheritRoll = true;
		SpringArm->bInheritYaw = true;
		SpringArm->bDoCollisionTest = false;
		bUseControllerRotationYaw = true;
		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
		break;
	}
}

// Called every frame
void AABCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SpringArm->TargetArmLength = FMath::FInterpTo(SpringArm->TargetArmLength, ArmLengthTo, DeltaTime, ArmLengthSpeed);

	switch (CurrentControlMode)
	{
	case EControlMode::DIABLO:
		SpringArm->RelativeRotation = FMath::RInterpTo(SpringArm->RelativeRotation, ArmRotationTo, DeltaTime, ArmRotationSpeed);
		break;
	}

}

// Called to bind functionality to input
void AABCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction(TEXT("ViewChange"), EInputEvent::IE_Pressed, this, &AABCharacter::ViewChange);
	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AABCharacter::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AABCharacter::LeftRight);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AABCharacter::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AABCharacter::LookUp);

}

void AABCharacter::UpDown(float NewAxisValue)
{
	switch (CurrentControlMode)
	{
	case EControlMode::GTA:
		AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), NewAxisValue);
		AddMovementInput(DirectionToMove);
		break;
	case EControlMode::DIABLO:
		AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), NewAxisValue);
		AddMovementInput(DirectionToMove);
		break;
	case EControlMode::SIDE:
		AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), NewAxisValue);
		AddMovementInput(DirectionToMove);
		break;
	case EControlMode::TOP:
		AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), NewAxisValue);
		AddMovementInput(DirectionToMove);
		break;
	case EControlMode::SHOULDER:
		AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), NewAxisValue);
		AddMovementInput(DirectionToMove);
		break;
	case EControlMode::FIRST:
		AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), NewAxisValue);
		AddMovementInput(DirectionToMove);
		break;
	}
}

void AABCharacter::LeftRight(float NewAxisValue)
{
	switch (CurrentControlMode)
	{
	case EControlMode::GTA:
		AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), NewAxisValue);
		AddMovementInput(DirectionToMove);
		break;
	case EControlMode::DIABLO:
		AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), NewAxisValue);
		AddMovementInput(DirectionToMove);
		break;
	case EControlMode::SIDE:
		AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), NewAxisValue);
		AddMovementInput(DirectionToMove);
		break;
	case EControlMode::TOP:
		AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), NewAxisValue);
		AddMovementInput(DirectionToMove);
		break;
	case EControlMode::SHOULDER:
		AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), NewAxisValue);
		AddMovementInput(DirectionToMove);
		break;
	case EControlMode::FIRST:
		AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), NewAxisValue);
		AddMovementInput(DirectionToMove);
		break;
	}
	

}

void AABCharacter::LookUp(float NewAxisValue)
{

	switch (CurrentControlMode)
	{
	case EControlMode::GTA:
		AddControllerPitchInput(NewAxisValue);
		break;
	case EControlMode::DIABLO:
		DirectionToMove.Y = NewAxisValue;
		break;
	case EControlMode::SIDE:
		AddControllerPitchInput(NewAxisValue);
		break;
	case EControlMode::TOP:
		AddControllerPitchInput(NewAxisValue);
		break;
	case EControlMode::SHOULDER:
		AddControllerPitchInput(NewAxisValue);
		break;
	case EControlMode::FIRST:
		CurrentAxis += -NewAxisValue;
		Camera->SetRelativeRotation(FRotator(CurrentAxis, 0.0f, 0.0f));
		break;
	}
}

void AABCharacter::Turn(float NewAxisValue)
{
	switch (CurrentControlMode)
	{
	case EControlMode::GTA:
		AddControllerYawInput(NewAxisValue);
		break;
	case EControlMode::DIABLO:
		DirectionToMove.X = NewAxisValue;
		break;
	case EControlMode::SIDE:
		AddControllerYawInput(NewAxisValue);
		break;
	case EControlMode::TOP:
		AddControllerYawInput(NewAxisValue);
		break;
	case EControlMode::SHOULDER:
		AddControllerYawInput(NewAxisValue);
		break;
	case EControlMode::FIRST:
		AddControllerYawInput(NewAxisValue);
		break;
	}
}

void AABCharacter::ViewChange()
{
	switch (CurrentControlMode)
	{
	case EControlMode::GTA:
		GetController()->SetControlRotation(GetActorRotation());
		SetControlMode(EControlMode::DIABLO);
		break;

	case EControlMode::DIABLO:
		GetController()->SetControlRotation(SpringArm->RelativeRotation);
		SetControlMode(EControlMode::SIDE);
		break;
	case EControlMode::SIDE:
		GetController()->SetControlRotation(SpringArm->RelativeRotation);
		SetControlMode(EControlMode::TOP);
		break;
	case EControlMode::TOP:
		GetController()->SetControlRotation(SpringArm->RelativeRotation);
		SetControlMode(EControlMode::SHOULDER);
		break;
	case EControlMode::SHOULDER:
		GetController()->SetControlRotation(SpringArm->RelativeRotation);
		SetControlMode(EControlMode::FIRST);
		break;
	case EControlMode::FIRST:
		GetController()->SetControlRotation(SpringArm->RelativeRotation);
		SetControlMode(EControlMode::GTA);
		break;
	}
}

