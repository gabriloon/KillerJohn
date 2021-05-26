// Fill out your copyright notice in the Description page of Project Settings.


#include "AINormalController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void AAINormalController::Tick(float DeltaTime) //AI 캐릭터의 시작위치 저장
{
    Super::Tick(DeltaTime);
}

void AAINormalController::BeginPlay() 
{
      Super::BeginPlay();
    if(BHShooter!=nullptr){//Behavior tree 가 있는지 확인
    RunBehaviorTree(BHShooter);
    GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"),GetPawn()->GetActorLocation());//AI 캐릭터의 시작 위치를 변수 'StartLocation' 에 할당
    }
}
