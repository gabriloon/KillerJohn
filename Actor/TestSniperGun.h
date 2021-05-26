// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestSniperGun.generated.h"

UCLASS()
class KILLERJOHN_API ATestSniperGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestSniperGun();
	virtual void Tick(float DeltaTime) override;
	void Shoot();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* GunMesh;

	UPROPERTY(EditAnywhere)
	UParticleSystem* GunEffect;//총 발사 효과
	
	UPROPERTY(EditAnywhere)
	USoundBase* ShotSound;//총 발사 소리

	UPROPERTY(EditAnywhere)
	USoundBase* ShotHitSound;//총 맞는 소리 

	UPROPERTY(EditAnywhere)
	UParticleSystem* ShootedEffect;//총 맞는 효과

	UPROPERTY(EditAnywhere)
	 float MaxRange=1000.0f; //총 최대 사거리

	UPROPERTY(EditAnywhere)
	 float GunDamage=10.0f; //총 데미지

	bool GunTrace(FHitResult& Hit,FVector& ShootRotation);

	AController* GetThisController() const;//Actor 또는 Character 의 Controller 추출
};

