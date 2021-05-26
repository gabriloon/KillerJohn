// Fill out your copyright notice in the Description page of Project Settings.


#include "DestroyActor.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ADestroyActor::ADestroyActor()//데미지 받으면 반응하는 Actor
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Root=CreateDefaultSubobject<USceneComponent>(TEXT("Root"));//0.Root
	SetRootComponent(Root);//루트
	ActorMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ActorMesh"));//1.Root 하위로 StaticMesh
	ActorMesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void ADestroyActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADestroyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float ADestroyActor::TakeDamage(float DamageAmount,struct FDamageEvent const &DamageEvent,class AController *EventInstrigator, AActor *DamageCauser) //총(데미지) 가 들어왔을 경우
{
	float Damaged=Super::TakeDamage(DamageAmount,DamageEvent,EventInstrigator,DamageCauser);
	Damaged=FMath::Min(Health,Damaged);//데미지가 최대 Health 를 넘으면 안된다.
	Health-=Damaged;//데미지에 따라 Health 감소

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),ShootedEffect,GetActorLocation(),GetActorRotation());//GetActorLocation 중심으로 파티클 효과 실행
	UGameplayStatics::PlaySoundAtLocation(GetWorld(),ShotHitSound,GetActorLocation());//GetActorLocation 중심으로 소리 재생

if(Health<=0)
{
Destroy();//Actor 삭제
}
return Damaged;
}

