// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_IsSeenPlayer.generated.h"

/**
 * 
 */
UCLASS()
class KILLERJOHN_API UBTService_IsSeenPlayer : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	public:
UBTService_IsSeenPlayer();

protected:
virtual void TickNode(UBehaviorTreeComponent &OwnerComp,uint8 *NodeMemory, float DeltaSeconds);
};

