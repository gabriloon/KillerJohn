// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "TestGun.h"
//#include "TestSniperGun.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "KillerJohnGameModeBase.h"
#include "Camera/CameraComponent.h"//시험
#include "Kismet/GameplayStatics.h"
#include "Misc/OutputDeviceNull.h"


// Sets default values
AShooterCharacter::AShooterCharacter()//적 캐릭터, 사용자의 캐릭터 기반을 구성하는 클래스
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}


// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetMesh()->HideBoneByName(TEXT("weapon_r"),EPhysBodyOp::PBO_None);//기존에 Shooter 마네킹 모델의 총을 없애주고
	if(!isPlayer)//적 캐릭터 일 경우 무기를 입수하는 동작 없이 무기가 장착되어 있어야한다.
	{Gun = GetWorld()->SpawnActor<ATestGun>(GunClass);
	Gun->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,TEXT("WeaponSocket1"));//WeaponSocket1 이라는 이름을 가진 소켓의 위치에 할당
	Gun->SetOwner(this);
	GunPose=true;//총을 쥐고 있는 자세인가? -> True
	}
	//InteractionBox->OnComponentBeginOverlap.AddDynamic(this,&AShooterCharacter::OnBoxBeginOverlap);//아이템 Inter작업2
	Health=MaxHealth;//시작시 최대(Default) HP
}


// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"),this, &AShooterCharacter::MoveForward);//W키,S키 입력시 호출
	PlayerInputComponent->BindAxis(TEXT("LookUp"),this, &APawn::AddControllerPitchInput);//마우스 Y 축 움직임
	PlayerInputComponent->BindAction(TEXT("GunSlot1"),EInputEvent::IE_Pressed,this, &AShooterCharacter::GunSlot1);//1번키
	PlayerInputComponent->BindAction(TEXT("GunSlot2"),EInputEvent::IE_Pressed,this, &AShooterCharacter::GunSlot2);//2번키

	PlayerInputComponent->BindAxis(TEXT("MoveRight"),this, &AShooterCharacter::MoveRight);//A키, D키
	PlayerInputComponent->BindAxis(TEXT("LookRight"),this, &APawn::AddControllerYawInput);//마우스 X 축 움직임
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);//SPACE 키
	PlayerInputComponent->BindAction(TEXT("Shoot"),EInputEvent::IE_Pressed,this, &AShooterCharacter::PullTrigger);//마우스 좌클릭
}

float AShooterCharacter::TakeDamage(float DamageAmount,struct FDamageEvent const &DamageEvent,class AController *EventInstrigator, AActor *DamageCauser) //데미지 입을때마다 호출
{
	float Damaged=Super::TakeDamage(DamageAmount,DamageEvent,EventInstrigator,DamageCauser);
	Damaged=FMath::Min(Health,Damaged);//데미지가 최대 Health 를 넘으면 안된다.
	Health-=Damaged;//데미지에 따라 Health 감소
	UE_LOG(LogTemp,Warning,TEXT("Health Life:%f"),Health);

if(IsDead()){//캐릭터가 죽었을 경우
	AKillerJohnGameModeBase* GameMode=GetWorld()->GetAuthGameMode<AKillerJohnGameModeBase>();
		if(GameMode!=nullptr){
		GameMode->PawnKilled(this);//EmGameModeBase cpp 의 PawnKilled 함수 호출
		this->GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);//죽인 캐릭터 Collision 제거
	}
	DetachFromControllerPendingDestroy();//컨트롤러에서 Pawn을 분리
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);//죽었으니까,캐릭터의 CapsuleCollision 제거
}
return Damaged;
}


bool AShooterCharacter::IsDead() const
{
	return Health<=0;
}

float AShooterCharacter::GetHealthPercent() const //Widget_Hud 에서 현재 HP 퍼센트를 위해 사용
{
	return Health/MaxHealth;
}

void AShooterCharacter::AddCurrentBullet() 
{
	TotalAmmo+=10;
}

void AShooterCharacter::WeaponCheck(int WC) //WC:1-AK 2-M4 3-SR, BP_Gun 쪽에서 총을 입수시에 시작하는 Function
{
	GunPose=true;//총 획득에 따라 bool 변경

	if(NextHold==1){//NextHold를 통해 총 휙득때마다 1,2번자리에 번갈아 장착되게
	LastWeaponCode=WC;//휙득한 총이 어떤 총인지
	GunSlot1();//1번칸에 총 휙득
	}
	else if(NextHold==2){
	LastWeaponCode2=WC;
GunSlot2();//2번칸에 총 휙득
	}
}

void AShooterCharacter::MoveForward(float Axis) //앞뒤 이동
{
	if(GunPose){//총을 쥔 자세인가 아닌가에 따라 속도 변경
	AddMovementInput(GetActorForwardVector()*Axis/2);}
	else{
		AddMovementInput((GetActorForwardVector()*Axis)/3);
	}
}

void AShooterCharacter::MoveRight(float Axis) //좌우 이동
{
	if(GunPose){//총을 쥔 자세인가 아닌가에 따라 속도 변경
	AddMovementInput(GetActorRightVector()*Axis/2);
	}
	else{
		AddMovementInput((GetActorRightVector()*Axis)/3);
	}
}

void AShooterCharacter::GunSlot1() //1번키에 총 할당
{	
	if(LastWeaponCode<0){//아무 총도 휙득 안했을 경우
UE_LOG(LogTemp,Warning,TEXT("You Dont Have Weapon"));
	}else{
		if(Gun!=nullptr)
		{
		Gun->Destroy();//새로운 총 휙득시에 기존에 장착되어 있는 총 삭제.
		}
	FActorSpawnParameters SpawnInfo;//액터 스폰 변수
	Gun=GetWorld()->SpawnActor<ATestGun>(DefaultInventoryClasses[LastWeaponCode],SpawnInfo);//스폰하면서 Gun 으로 할당
	Gun->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,TEXT("WeaponSocket"));//위치를 WeaponSocket 으로 이동
	Gun->GunMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);//총 자체의 Collision 제거
	Gun->SetOwner(this);
	SettingGunAboutChange();//총의 종류에 따라 탄환 개수 변경, 반동 변경
	if(FirstHold){//처음 웨폰 스위칭 시에 2번 무기에 아무것도 장착되어 있지 않을경우 무기 휙득시 자동으로 2번으로 가기위한 방법.
	NextHold=2;
	}else{
	NextHold=1;
	}
	}
}

void AShooterCharacter::GunSlot2() //2번키에 총 할당
{
	if(LastWeaponCode2<0){//아무 총도 휙득 안했을 경우
UE_LOG(LogTemp,Warning,TEXT("You Dont Have Weapon"));
	}
	else{
	if(Gun!=nullptr)
	{Gun->Destroy();}//새로운 총 휙득시에 기존에 장착되어 있는 총 삭제.
	FActorSpawnParameters SpawnInfo;//액터 스폰 변수
	Gun=GetWorld()->SpawnActor<ATestGun>(DefaultInventoryClasses[LastWeaponCode2],SpawnInfo);//스폰하면서 Gun 으로 할당
	Gun->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,TEXT("WeaponSocket"));//위치를 WeaponSocket 으로 이동
	Gun->GunMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);//총 자체의 Collision 제거
	Gun->SetOwner(this);
	SettingGunAboutChange();
	if(FirstHold){//이제 1,2번 다 무기가 있으니까 FirstHold 변수 변경하면서 불필요하다 
	FirstHold=false;
	NextHold=2;
	}else{
	NextHold=2;
	}
	}
}




AController* AShooterCharacter::GetThisController() const//Character 의 Controller 리턴
{
	APawn* OwnerPawn= Cast<APawn>(GetOwner());
	if(OwnerPawn==nullptr)return nullptr;
	return OwnerPawn->GetController();
}


void AShooterCharacter::PullTrigger() //PullTrigger -> Gun 의 Shoot 함수 순서로 전달
{
	if(Gun==nullptr){
		return;
	}
	//Gun->SetActorHiddenInGame(!EnableShoot);
	if(currentAmmo<=0)//현재 사용하는 총의 총알이 없을경우
	{
	return;
	}
	else if(EnableShoot){//총을 쏠 수 있는 상태인가
	GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(RifleGunShake);//카메라 움직임
	currentAmmo-=1;//탄창에서 한발씩 감소
	TotalAmmo-=1;//가지고 있는 특정 총알의 총 개수에서 한발씩 감소
	Gun->Shoot();//카메라의 정면의 Raycast 를 통해 총알이 발사되는 함수
	//AController* Test = GetThisController();
	UE_LOG(LogTemp,Display,TEXT("RecoilPitch: %f"), GunRecoilPitch);
	UE_LOG(LogTemp,Display,TEXT("RecoilPitch: %f"), GunRecoilYaw);
	UE_LOG(LogTemp,Display,TEXT("currentAmmo: %d"), currentAmmo);
	UE_LOG(LogTemp,Display,TEXT("ARRifleAmmo: %d"), TotalAmmo);
	this->AddControllerPitchInput(GunRecoilPitch);//위아래 반동
	this->AddControllerYawInput(GunRecoilYaw);//좌우 반동
	}
}

void AShooterCharacter::GunReload() //장전을 위한 함수, TotalAmmo: 총 총알수 AmCount:현재 탄창의 남은 총알 수
{
	if(TotalAmmo<=0){//총알이 없을 경우
		UE_LOG(LogTemp,Warning,TEXT("Ammo is Zero"));
		return;
	}else{
		if(TotalAmmo<Ammolimit){//전체 남은 총알이 탄창에 들어갈 수 있는 총알보다 적을경우
			currentAmmo=TotalAmmo;//남은 전체 총알을 탄창에 집어넣는다.
			TotalAmmo=0;
		}else{
			currentAmmo=Ammolimit;//탄창에 들어갈 수 있는 만큼 집어넣는다.//currentAmmo 의 총알 개수의 감소는 이미 PullTrigger 함수에서 실행
		}
	}
}

bool AShooterCharacter::GetGunPose() const//현재 총을 쥔 자세인가.
{
	return GunPose;
}

void AShooterCharacter::SetGunPose(bool isGunPose) 
{
	GunPose=isGunPose;
}

void AShooterCharacter::SettingGunAboutChange(){//AR:0 SR:1

	//총이 가지고 있는 변수를 이 클래스의 변수에 저장.
	WeaponCode=Gun->GunCode;//현0재 쥐고 있는 총의 종류에 따라 변화
	GunRecoilPitch=Gun->ReturnRecoilPitch();//BP_Gun 에서 총마다 다르게 설정 반동 참고
	GunRecoilYaw=Gun->ReturnRecoilYaw();
	Ammolimit=Gun->SetMaxAmmo;//탄창에 들어갈 수 있는 총알의 개수도 변경
	currentAmmo=0;

if(WeaponCode==1){//쥐고 있는 총일 SR 일때
		if(!FirstHold)
		{SniperAmmo=TotalAmmo;//그래서 총을 쓰고 바꾸게 된다고 해도 SniperAmmo 즉 근본 총알이 줄어드는게 아니어서 2번누르고 1번만 눌러도 Total 은 계속 SniperAmmo 의 값이 된다.
		//총 종류(ex.권총,샷건) 추가될시 똑같이 설정
		}
	TotalAmmo=ARRifleAmmo;
	}
	else if(WeaponCode==0){//쥐고 있는 총일 AR 일때
		if(!FirstHold)
		{ARRifleAmmo=TotalAmmo;}
	TotalAmmo=SniperAmmo;
	}
	
	//그래서 이 클래스에서 원할때 Gun-> 호출대신에 저장된 변수를 통해 호출
}