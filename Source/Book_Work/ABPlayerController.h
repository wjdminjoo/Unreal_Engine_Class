// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Book_Work.h"
#include "GameFramework/PlayerController.h"
#include "ABPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BOOK_WORK_API AABPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	
public:
	virtual void PostInitializeComponents() override;
	virtual void Possess(APawn* aPawn) override;

protected:
	virtual void BeginPlay() override;
	
};
