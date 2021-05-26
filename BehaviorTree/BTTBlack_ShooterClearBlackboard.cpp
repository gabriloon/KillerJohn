// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTBlack_ShooterClearBlackboard.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTBlack_ShooterClearBlackboard::UBTTBlack_ShooterClearBlackboard() //Blackboard 의 Key 값 초기화
{
    NodeName="Clear Blackboard Value";
}

EBTNodeResult::Type UBTTBlack_ShooterClearBlackboard::ExecuteTask(UBehaviorTreeComponent &OwnerTemp, uint8 *NodeMemory) 
{
    Super::ExecuteTask(OwnerTemp,NodeMemory);

    OwnerTemp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());

    return EBTNodeResult::Succeeded;
}
