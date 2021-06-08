// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KillerJohnGameModeBase.h"
#include "ShooterCharacter.h"
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


	UFUNCTION(BlueprintPure)
	int StageInfo() const; //플레이어가 죽인 적의 수를 위젯에 반영하기 위해서 Get 으로 수 리턴

 void EndGame(bool IsPlayerWin);

UPROPERTY(VisibleAnywhere)
int KillClear=0;

};
