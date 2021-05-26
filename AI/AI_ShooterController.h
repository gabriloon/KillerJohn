// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AI_ShooterController.generated.h"

/**
 * 
 */
UCLASS()
class KILLERJOHN_API AAI_ShooterController : public AAIController
{
	GENERATED_BODY()
	

	public:
		virtual void Tick(float DeltaTime) override;
		bool IsDead() const;
	protected:
		virtual void BeginPlay() override;


	private:
	UPROPERTY(EditAnywhere)
	float ShootDistance=200.0f;
	
	UPROPERTY(EditAnywhere)
	class UBehaviorTree* BHShooter;
	

};
