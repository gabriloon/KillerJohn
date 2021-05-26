// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_ShooterController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterCharacter.h"

void AAI_ShooterController::BeginPlay() //AI 캐릭터의 시작위치 저장, IsDead 를 통한 살아있는지 확인
{
    Super::BeginPlay();

    if(BHShooter!=nullptr){//Behavior tree 가 있는지 확인
    RunBehaviorTree(BHShooter);
  //APawn* PlayerPawn=UGameplayStatics::GetPlayerPawn(GetWorld(),0);
  //GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"),PlayerPawn->GetActorLocation());
  GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"),GetPawn()->GetActorLocation());//AI 캐릭터의 시작 위치를 Key 'StartLocation' 에 할당
  }

}

void AAI_ShooterController::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);
}

bool AAI_ShooterController::IsDead() const
{
  AShooterCharacter* ControllerCharacter=Cast<AShooterCharacter>(GetPawn());

  if(ControllerCharacter!=nullptr){
return ControllerCharacter->IsDead();//ShooterCharacter cpp 에서 Health<=0 일 True 리턴
}
  return true;
}
