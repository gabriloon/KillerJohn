// Fill out your copyright notice in the Description page of Project Settings.


#include "DontDestroyActor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADontDestroyActor::ADontDestroyActor()//DestroyActor 와 비슷하지만 차이점은 데미지를 입었을때 Destroy 대신에 Material 변경
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Root=CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);//루트
	ActorMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ActorMesh"));//총의 겉모습
	ActorMesh->SetupAttachment(Root);
	MaterialOne=CreateDefaultSubobject<UMaterialInterface>(TEXT("MaterialOne"));

}

// Called when the game starts or when spawned
void ADontDestroyActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADontDestroyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ADontDestroyActor::TakeDamage(float DamageAmount,struct FDamageEvent const &DamageEvent,class AController *EventInstrigator, AActor *DamageCauser) 
{
	float Damaged=Super::TakeDamage(DamageAmount,DamageEvent,EventInstrigator,DamageCauser);
	ActorMesh->SetMaterial(1,MaterialOne);	//블루프린트에서 설정한 메터리얼로 변경
	UGameplayStatics::PlaySoundAtLocation(GetWorld(),ShotHitSound,GetActorLocation());//GetActorLocation()을 중심으로 소리 재생

return Damaged;
}

