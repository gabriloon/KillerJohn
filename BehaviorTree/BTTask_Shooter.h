// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Shooter.generated.h"

/**
 * 
 */
UCLASS()
class KILLERJOHN_API UBTTask_Shooter : public UBTTaskNode
{
	GENERATED_BODY()
	
	public:
	UBTTask_Shooter();

	protected:
		virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &OwnerTemp, uint8 *NodeMemory) override;
};
