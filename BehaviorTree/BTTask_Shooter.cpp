// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shooter.h"
#include "AIController.h"
#include "ShooterCharacter.h"


UBTTask_Shooter::UBTTask_Shooter() //AI 가 총쏘기 위한 Task 
{
    NodeName="Shoot";
}

EBTNodeResult::Type UBTTask_Shooter::ExecuteTask(UBehaviorTreeComponent &OwnerTemp, uint8 *NodeMemory) 
{
    Super::ExecuteTask(OwnerTemp,NodeMemory);
    if(OwnerTemp.GetAIOwner()==nullptr){
        return EBTNodeResult::Failed;
    }

    AShooterCharacter* Character= Cast<AShooterCharacter>(OwnerTemp.GetAIOwner()->GetPawn());//AI 캐릭터
    if(Character==nullptr){
    return EBTNodeResult::Failed;
    }
    Character->PullTrigger();//총 쏘는 함수

    
    return EBTNodeResult::Succeeded;
}