// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_RandomLocationSet.generated.h"

/**
 * 
 */
UCLASS()
class KILLERJOHN_API UBTTask_RandomLocationSet : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
		
public:
	UBTTask_RandomLocationSet();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &OwnerTemp, uint8 *NodeMemory) override;
};
