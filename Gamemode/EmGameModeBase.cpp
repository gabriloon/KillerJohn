// Fill out your copyright notice in the Description page of Project Settings.


#include "EmGameModeBase.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "AI_ShooterController.h"
#include "Misc/OutputDeviceNull.h"

void AEmGameModeBase::PawnKilled(APawn* PawnKilled) //ShooterPlayerCharacter.cpp 의 TakeDamage 함수에서 IsDead 가 True 일 경우 호출
{
    Super::PawnKilled(PawnKilled);

   APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());//캐릭터의 Controller 호출 및 설정
    if(PlayerController!=nullptr){//죽은게 플레이어 일경우
       EndGame(false);
    }
for(AAI_ShooterController* Controller:TActorRange<AAI_ShooterController>(GetWorld()))//Controller 의 수,즉 적 캐릭터의 수 만큼 반복
{
if(!Controller->IsDead()){//적 캐릭터가 전부 죽을때까지 return 을 통해 끝내지 않는다.
    return;
}
}

    EndGame(true);//모든 적 캐릭터가 죽었을 경우에
}


void AEmGameModeBase::EndGame(bool IsPlayerWin) 
{
for(AController* Controller:TActorRange<AController>(GetWorld())){
bool IsPlayer=Controller->IsPlayerController()==IsPlayerWin;//플레이어가 승패 결과를 bool 로써 저장 후 전송
Controller->GameHasEnded(Controller->GetPawn(),IsPlayer); //ShooterPlayerController.cpp 의 GameHasEnded 로 전송
}
}
