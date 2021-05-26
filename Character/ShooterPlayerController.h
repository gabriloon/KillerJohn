// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"


/**
 * 
 */
UCLASS()
class KILLERJOHN_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()


protected:
	virtual void BeginPlay() override;
	public: 
		virtual void GameHasEnded(class AActor* EndGameFocus=nullptr,bool bIsWinner=false) override;
	private:

FTimerHandle RestartTimer;

	UPROPERTY(EditAnywhere)
	float RestartDelay=5.0f;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget>LoseScreenClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget>WinScreenClass;


	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget>Hud;

	UPROPERTY()
	UUserWidget* HudScreen;

};
