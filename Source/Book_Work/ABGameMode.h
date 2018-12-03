// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Book_Work.h"
#include "GameFramework/GameModeBase.h"
#include "ABGameMode.generated.h"

/**
 * 
 */
UCLASS()
class BOOK_WORK_API AABGameMode : public AGameModeBase
{
	GENERATED_BODY()


		AABGameMode();
	
public:
	virtual void PostLogin(APlayerController* NewPlayer) override;
	
	
};
