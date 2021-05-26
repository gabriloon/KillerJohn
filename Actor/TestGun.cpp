// Fill out your copyright notice in the Description page of Project Settings.


#include "TestGun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"


// Sets default values
ATestGun::ATestGun()//총 Actor 구성 cpp
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root=CreateDefaultSubobject<USceneComponent>(TEXT("Root"));//0.Root
	SetRootComponent(Root);//루트
	GunMesh=CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMesh"));//1. 총의 SkeletalMesh
	GunMesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void ATestGun::BeginPlay()
{
	Super::BeginPlay();
}

void ATestGun::Shoot() //ShooterCharacter의 PullTrigger함수 내에서 실행
{
	UGameplayStatics::SpawnEmitterAttached(GunEffect,GunMesh,TEXT("MuzzleFlashSocket"));
	//MuzzleFlashSocket 부분에서 파티클 효과 재생	
	UGameplayStatics::SpawnSoundAttached(ShotSound,GunMesh,TEXT("MuzzleFlashSocket"));
	//MuzzleFlashSocket 부분에서 소리 재생	
	FHitResult Hit;
	FVector ShootRotation;
	bool bSuccess= GunTrace(Hit,ShootRotation);//총 맞은 Hit 포인트, 총 맞은곳의 반대면

	if(bSuccess){//총을 맞췄을 경우
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),ShootedEffect,Hit.Location,ShootRotation.Rotation());//총알 맞은 Particle 실행
	UGameplayStatics::PlaySoundAtLocation(GetWorld(),ShotHitSound,Hit.Location);//소리 재생
	AActor* HitActor = Hit.GetActor();//Hit Point 간격에 있는, 즉 총 맞은 Actor 
	if(HitActor!= nullptr){//Actor가 있을경우
	FPointDamageEvent DamageEvent(GunDamage,Hit,ShootRotation,nullptr);//DamageEvent 전달을 위한 변수 선언
	AController* OwnerController = GetThisController();
	HitActor->TakeDamage(GunDamage,DamageEvent,OwnerController,this);//총알 맞은 Actor가 TakeDamage 함수 실행
	}
}
}

// Called every frame
void ATestGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ATestGun::GunTrace(FHitResult& Hit,FVector& ShootRotation) 
{//이 객체를 가지고 있는 플레이어를 불러와 총의 범위 Line Trace 로 측정후 가능한지 안한지 리턴
	AController* OwnerController=GetThisController();
	//플레이어 컨트롤러 호출하기 위한 함수
	if(OwnerController==nullptr)return false;
	
	FVector Location;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(Location,Rotation);//플레이어 관점
	FVector End= Location+Rotation.Vector() *MaxRange;//플레이어 시각부터 *MaxRange 거리까지
	ShootRotation= -Rotation.Vector();//총을 맞은 반대180도에서 파티클 효과 발생을 위해서
	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(this);//이 객체(총) 무시
	TraceParams.AddIgnoredActor(GetOwner());//이 객체(총)를 들고 있는 캐릭터 무시

	return GetWorld()->LineTraceSingleByChannel(Hit, Location, End,ECollisionChannel::ECC_GameTraceChannel1,TraceParams);
	//End 까지 직선으로 감지
}

AController* ATestGun::GetThisController() const
{
	APawn* OwnerPawn= Cast<APawn>(GetOwner());
	if(OwnerPawn==nullptr)return nullptr;
	return OwnerPawn->GetController();
}

float ATestGun::ReturnRecoilPitch()  //위 아래 반동 값 특정 구간 랜덤을 통해 전달
{
	return FMath::RandRange(RecoilPitchMin,RecoilPitchMax);
}

float ATestGun::ReturnRecoilYaw() //좌우 반동 값 특정 구간 랜덤을 통해 전달
{
	return FMath::RandRange(RecoilYawMin,RecoilYawMax);
}