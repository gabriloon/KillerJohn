// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DestroyActor.generated.h"

UCLASS()
class KILLERJOHN_API ADestroyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADestroyActor();

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
	float Health=100.0f;

	UPROPERTY(EditAnywhere)
	USoundBase* ShotHitSound;//Actor 맞는 소리

	UPROPERTY(EditAnywhere)
	UParticleSystem* ShootedEffect;//Actor 맞는 효과

};
