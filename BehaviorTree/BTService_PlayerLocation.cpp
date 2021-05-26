// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocation.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTService_PlayerLocation::UBTService_PlayerLocation() //플레이어 위치 Tick(매순간)내에서 Blackboard의 Key 로 매순간 할당
{
    NodeName="Update Player Location";
}


void UBTService_PlayerLocation::TickNode(UBehaviorTreeComponent &OwnerComp,uint8 *NodeMemory, float DeltaSeconds) 
{
    Super::TickNode(OwnerComp,NodeMemory,DeltaSeconds);
    APawn* PlayerPawn=UGameplayStatics::GetPlayerPawn(GetWorld(),0);

    if(PlayerPawn==nullptr)
    {return;}

    OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(),PlayerPawn->GetActorLocation());//플레이어 위치 Blackboard의 Key 로 할당
}


