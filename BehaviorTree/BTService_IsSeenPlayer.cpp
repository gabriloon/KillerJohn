// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_IsSeenPlayer.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_IsSeenPlayer::UBTService_IsSeenPlayer() //Tick(매순간)내에서 플레이어 확인 후 플레이어의 위치를 확인
{
    NodeName="Is Seen Player";
}

void UBTService_IsSeenPlayer::TickNode(UBehaviorTreeComponent &OwnerComp,uint8 *NodeMemory, float DeltaSeconds) 
{
     Super::TickNode(OwnerComp,NodeMemory,DeltaSeconds);

     APawn* PlayerPawn=UGameplayStatics::GetPlayerPawn(GetWorld(),0);
 if(PlayerPawn==nullptr)
    {return;}
 if(OwnerComp.GetAIOwner()==nullptr)
    {return;}

if(OwnerComp.GetAIOwner()->LineOfSightTo(PlayerPawn)){//플레이어 위치 회전을 통해 처다보게
    OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(),PlayerPawn);//플레이어 위치 Blackboard의 Key 로 할당
}
else{
OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());//플레이어가 안보이면 플레이어 위치 Blackboard의 Key를 Clear
}

}
