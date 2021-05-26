// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KillerJohnGameModeBase.h"
#include "EmGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class KILLERJOHN_API AEmGameModeBase : public AKillerJohnGameModeBase
{
	GENERATED_BODY()
	
public:
 virtual void PawnKilled(APawn* PawnKilled)override;
 void EndGame(bool IsPlayerWin);
};
