// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

void AShooterPlayerController::GameHasEnded(class AActor* EndGameFocus,bool bIsWinner) //EmGameModeBase cpp 에서 호출 받아 실행
{
    Super::GameHasEnded(EndGameFocus,bIsWinner);
  HudScreen->RemoveFromViewport();//기존에 Aim, HP 보이는 Widget 제거
    if(bIsWinner){//플레이어가 이겼는가?
UUserWidget* WinScreen=CreateWidget(this,WinScreenClass);//이겼다는 위젯 표시
if( WinScreen!=nullptr){
 WinScreen->AddToViewport();
}
}else{
UUserWidget* LoseScreen=CreateWidget(this,LoseScreenClass);//졌다는 위젯 표시
if(LoseScreen!=nullptr){
LoseScreen->AddToViewport();
}
}
    GetWorldTimerManager().SetTimer(RestartTimer,this,&APlayerController::RestartLevel,RestartDelay);//RestartDelay 시간 후에 자동으로 게임 재시작
}

void AShooterPlayerController::BeginPlay() //Widget 영향
{
    Super::BeginPlay();
   
   FTimerHandle WaitHandle;
   GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
   {
 HudScreen=CreateWidget(this,Hud);
    if(HudScreen!=nullptr){
        HudScreen->AddToViewport();//Hud Widget: Aim, HP 표시 ,,,목표 위젯의 경우에는 BP 에서 CreateWidget,AddToViewport 작업을 진행한다
    }
   }), 7.0f, false);//처음에 시네마틱 영상에 안보이게 하기위해서 Delay(7초)를 주고 Widget 생성
   
}