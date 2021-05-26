// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_RandomLocationSet.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_RandomLocationSet::UBTTask_RandomLocationSet() //플레이어가 가야될 위치를 X,Y,Z(15.0f) 의 랜덤으로 Blackboard 의 Key 로 할당 
{
    NodeName="RandomLocationSet";
}

EBTNodeResult::Type UBTTask_RandomLocationSet::ExecuteTask(UBehaviorTreeComponent &OwnerTemp, uint8 *NodeMemory) 
{
    Super::ExecuteTask(OwnerTemp,NodeMemory);
    float randomX=FMath::RandRange(-1785.0f,1700.0f);//X 랜덤
    float randomY=FMath::RandRange(-1040.0f,1360.0f);//Y 랜덤
    OwnerTemp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(),FVector(randomX,randomY,15.0f));//BlackBoard의 Key 로 할당
    return EBTNodeResult::Succeeded;
}
