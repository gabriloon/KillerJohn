// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "ShooterCharacter.generated.h"


class ATestGun;
class ATestSniperGun;

UCLASS()
class KILLERJOHN_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

	void PullTrigger();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

UPROPERTY(EditDefaultsOnly, Category="Inventory")
TArray<TSubclassOf<class ATestGun>> DefaultInventoryClasses;//블루프린트에서 총 배열 저장을 위한 선언

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount,struct FDamageEvent const &DamageEvent,class AController *EventInstrigator, AActor *DamageCauser) override;
	//데미지를 입었을 경우 처리 함수

	UFUNCTION(BlueprintPure)
	bool IsDead() const;//살아있는지 죽었는지 Return
	
	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const; //현재 HP UI 에 반영하기 위한 함수

	UFUNCTION(BlueprintCallable)
	void WeaponCheck(int WeaponCode); //DefaultInventoryClasses 블루프린트에서 설정한 총 액터(ATestGun)들을 순서대로인 Code 번호를 통해 읽어와 정확히 Actor 를 불러온다. 

	UFUNCTION(BlueprintCallable)
	void GunReload();//재장전 관련 함수

	UFUNCTION(BlueprintPure)
	bool GetGunPose() const;//총알이 없는데 총을 들고 있을경우를 위해, bool GunPose 와 연동

	UFUNCTION(BlueprintCallable)
	void SetGunPose(bool isGunPose);//총알이 없는데 총을 들고 있을경우를 위해, bool GunPose 와 연동

private:
	void MoveForward(float Axis); //캐릭터 앞뒤 이동
	void MoveRight(float Axis);//좌우 이동
	void GunSlot1();//...?
	void GunSlot2();
	//void LookUp(float MouseY);

	UPROPERTY(EditAnywhere)
	float MaxHealth=100.0f;

	UPROPERTY(VisibleAnywhere)
	float Health;//현재 HP

	UPROPERTY(VisibleAnywhere)
	int LastWeaponCode=-1;//이 코드 값을 통해 
	UPROPERTY(VisibleAnywhere)
	int LastWeaponCode2=-1;

	int NextHold=1;
	bool FirstHold=true;
	
	UPROPERTY(EditAnywhere)
	bool isPlayer=false;//플레이어 일경우 시작 시에 총 없이 존재하기 위한 bool 설정

	AController* GetThisController() const;

	UPROPERTY(EditAnywhere)
	bool EnableShoot=true;//총알이 없는데 총을 들고 있을경우를 위해

	UPROPERTY(EditAnywhere)
	bool GunPose=false;//총을 쥐고 있는지 확인후에 참이면 True 

UPROPERTY(EditDefaultsOnly)
TSubclassOf<ATestGun>GunClass;

UPROPERTY(EditAnywhere,Category="Effects")
TSubclassOf<UCameraShake> RifleGunShake;//총 쏠시 카메라 흔들림

UPROPERTY(EditAnywhere)
ATestGun* Gun;

float GunRecoilPitch; //총의 반동
float GunRecoilYaw;

UPROPERTY(EditAnywhere)
int ARRifleAmmo=50;//사용자가 가지고 있는 AR 총알수

UPROPERTY(EditAnywhere)
int SniperAmmo=20;//사용자가 가지고 있는 SR 총알수

UPROPERTY(EditAnywhere)
int TotalAmmo=50;//AR 총알이든 SR 총알이든 사용하기전에 TotalAmmo 로 옮겨서 사용

UPROPERTY(VisibleAnywhere)
int currentAmmo=20;//현재 탄창의 총알 AI 가 5발쏘고 마는 이유

UPROPERTY(VisibleAnywhere)
int Ammolimit=20;//탄창안에 들어갈수 있는 최대 총알 수 Gun->SetMaxAmmo 읽어와 저장

int WeaponCode=0;//총이 어떤 총인지 알기위해서 Gun-> GunCode에서 읽어와 저장 
//LastWeaponCode 대신에 변수하나를 생성해 이거 쓰는 이유는 LastWeaponCode는 각각의 총 매쉬, 설정값 등을 구별하기 위해 사용하는데 
//이건 총의 유형 AR(0),SR(1) 등을 구변하는데 사용한다. 


void SettingGunAboutChange();

};
