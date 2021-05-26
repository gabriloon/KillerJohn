// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DontDestroyActor.generated.h"

UCLASS()
class KILLERJOHN_API ADontDestroyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADontDestroyActor();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ActorMesh;
	
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float DamageAmount,struct FDamageEvent const &DamageEvent,class AController *EventInstrigator, AActor *DamageCauser) override;


private:

	UPROPERTY(EditAnywhere)
	USoundBase* ShotHitSound;//Actor 맞는 소리

	UPROPERTY(EditAnywhere,Category="Materials")
	UMaterialInterface* MaterialOne;

	UPROPERTY(EditAnywhere,Category="Materials")
	UMaterialInstance* MaterialInstance;//보류

	UPROPERTY(EditAnywhere,Category="Materials")
	bool bFullDestroy=true;

};

