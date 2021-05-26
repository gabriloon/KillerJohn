// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShooterCharacter.h"//Test
#include "TestGun.generated.h"

UCLASS()
class KILLERJOHN_API ATestGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestGun();
	virtual void Tick(float DeltaTime) override;
	void Shoot();

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* GunMesh;

	float ReturnRecoilPitch();//총 반동 return 함수
	float ReturnRecoilYaw();

	UPROPERTY(EditAnywhere)
	int SetMaxAmmo=7;//탄창에 최대 총알개수 AR:20 SR:5

	UPROPERTY(EditAnywhere)
	int GunCode=0;//SR:0 AR:1
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	class AShooterCharacter* MyPawn;//Test
	

private:

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

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

	UPROPERTY(EditAnywhere)
	float RecoilPitchMin=-0.1; //총 반동 최소
	UPROPERTY(EditAnywhere)
	float RecoilPitchMax=-0.02; //총 반동 최대
	UPROPERTY(EditAnywhere)
	float RecoilYawMin=-0.1; //총 반동 최소
	UPROPERTY(EditAnywhere)
	float RecoilYawMax=-0.02; //총 반동 최대
	

	bool GunTrace(FHitResult& Hit,FVector& ShootRotation);

	AController* GetThisController() const;//Actor 또는 Character 의 Controller 추출


};
