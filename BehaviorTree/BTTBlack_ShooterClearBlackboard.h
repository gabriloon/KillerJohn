// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTBlack_ShooterClearBlackboard.generated.h"

/**
 * 
 */
UCLASS()
class KILLERJOHN_API UBTTBlack_ShooterClearBlackboard : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTTBlack_ShooterClearBlackboard();

protected:
	//virtual	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) override;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &OwnerTemp, uint8 *NodeMemory) override;
};
