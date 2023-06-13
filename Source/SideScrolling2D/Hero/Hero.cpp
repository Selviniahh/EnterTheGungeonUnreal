// Fill out your copyright notice in the Description page of Project Settings.


#include "Hero.h"
#include "PaperFlipbookComponent.h"
#include "PaperZDAnimationComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "SideScrolling2D/Guns/GunBase.h"
#include "Components/BoxComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

// Sets default values
AHero::AHero()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
    BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetGenerateOverlapEvents(true);
    RootComponent = BoxComponent;

    FlipBook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("FlipBook"));
    FlipBook->SetupAttachment(BoxComponent);

    HandComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("HandComponent"));
    HandComponent->SetupAttachment(BoxComponent);
	HandComponent->SetVisibility(true);

	HandSocket = CreateDefaultSubobject<USceneComponent>(TEXT("HandSocket"));
	HandSocket->SetupAttachment(HandComponent);

    HeroAnimation = CreateDefaultSubobject<UPaperZDAnimationComponent>(TEXT("HeroAnimation"));
	HeroAnimation->InitRenderComponent(FlipBook);
	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));

}

// Called when the game starts or when spawned
void AHero::BeginPlay()
{
	Super::BeginPlay();
	Gun = nullptr;
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AHero::OnBoxComponentBeginOverlap);
	
	PlayerController = Cast<APlayerController>(GetController());

	if (PlayerController)
	{
		//Enhanced input initialization shits
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
		
		PlayerController->bShowMouseCursor = true;
	}

	Ranges = {
		{1,55}, //Right
		{55,75}, //Front Hand Right
		{75,115}, //Front Hand Left
		{115,190}, //Left
		{190,245}, //Diagonal_Left
		{245,265}, //Back_Hand_Left
		{265,290}, //Back_Hand_Right
		{290,310}, //Diagonal_Right
		//310-360 is Right
	};
	
	SetDirectionBasedOnEnum = {
		{EDirections::Right, FVector2D(1.0, 0.0)},
		{EDirections::Front_Hand_Right, FVector2D(-1.0, -1.0)},
		{EDirections::Front_Hand_Left, FVector2D(-1.0, -1.0)},
		{EDirections::Left, FVector2D(-1.0, 0.0)},
		{EDirections::Back_Diagonal_Left, FVector2D(-1.0, 1.0)},
		{EDirections::Back_Hand_Left, FVector2D(0, 1.0)},
		{EDirections::Back_Hand_Right, FVector2D(0, 1.0)},
		{EDirections::Back_Diagonal_Right, FVector2D(1.0, 1.0)},
	};


}

void AHero::FlipComponents()
{
	// Set Flip for Dash
	 if (IsDashingCpp)
	 {
	 	//Trim to 3 digits. 
	 	FVector2D RoundedMoveDirection(FMath::RoundHalfToEven(MoveDirection.X * 1000) / 1000, FMath::RoundHalfToEven(MoveDirection.Y * 1000) / 1000);

	 	if (RoundedMoveDirection == FVector2D(-0.707,0.707) || RoundedMoveDirection == FVector2D(-0.707,-0.707) || RoundedMoveDirection == FVector2D(-1.0,0.0))
	 	{
	 		UE_LOG(LogTemp, Display, TEXT("Flipping"));
	
	 		FlipBook->SetRelativeScale3D(FVector(-1.0,-1.0,1.0));
	 	}
	 	else
	 	{
	 		UE_LOG(LogTemp, Display, TEXT("Revert Flip"));
	 		FlipBook->SetRelativeScale3D(FVector(1.0,1.0,1.0));
	 	}
	 }
	
	 //Set Flip for other directions
	 else
	{
		//Revert Flip
		if (CurrentDirection == Right || CurrentDirection == Front_Hand_Right || CurrentDirection == Back_Diagonal_Right || CurrentDirection == Back_Hand_Right)
		{
			FlipBook->SetRelativeScale3D(FVector(1.0,1.0,1.0));
			HandComponent->SetRelativeLocation(FVector(7.0,0,-4.0));
			HandSocket->SetRelativeScale3D(FVector(1.0,1.0,1.0));
			HandSocket->SetRelativeRotation(FRotator(MouseAngle * -1,0,90));
		}
		//Flip
		else
		{
			FlipBook->SetRelativeScale3D(FVector(-1.0,-1.0,1.0));
			HandComponent->SetRelativeLocation(FVector(-10.0,0,-4.0));
			HandSocket->SetRelativeScale3D(FVector(1.0,-1.0,1.0));
			HandSocket->SetRelativeRotation(FRotator(MouseAngle * -1,0,90));
		}
	}
	
	
}

void AHero::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (PlayerController)
	{
		GetAngle();
	}
	
	SetMouseDirectionEnum();
	FlipComponents();

	Dash(DeltaTime);
}

void AHero::Move(const FInputActionValue& Value)
{
	if (!IsDashingCpp)
	{
		MoveDirection = Value.Get<FVector2D>();
	}
	
	if (MoveDirection.SquaredLength() > 1)
	{
		MoveDirection.Normalize();
	}
	
	//I had to - for MoveDirection because Enhanced movement wants like that.
	const FVector MovementVector3D(MoveDirection.X, -MoveDirection.Y, 0);
	
	AddMovementInput(MovementVector3D);
}

void AHero::Shoot(const FInputActionValue& Value)
{
	//For Completed Dash Action, Is Shooting set to false
	IsShooting = true;

	if (Gun)
	{
		Gun->Shoot();
	}
}

void AHero::Dash(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Display, TEXT("Dash is running:"));

	//I guess I will never need it's action values
	bool DashClicked = Value.Get<bool>();

	//Start Dashing and apply changes
	if (DashTimer == 0)
	{
		IsDashingCpp = true;
		MovementComponent->MaxSpeed = 300;
		HandComponent->SetVisibility(false);
		if (Gun) Gun->FlipBook->SetVisibility(false);
		DashTimer = 0;
	}
}

void AHero::OnBoxComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Gun"))
	{
		Gun = Cast<AGunBase>(OtherActor);

		const FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, true);
		Gun->FlipBook->AttachToComponent(HandSocket,AttachmentTransformRules);
	}
}

void AHero::GetAngle()
{
	// Screen position of the mouse
	float MouseX, MouseY;
	PlayerController->GetMousePosition(MouseX, MouseY);

	// Screen position of the player
	FVector2D ScreenLocation;
	PlayerController->ProjectWorldLocationToScreen(GetActorLocation(), ScreenLocation);

	// Vector from the player to the mouse cursor in screen space
	FVector2D ScreenPlayerToMouse = FVector2D(MouseX, MouseY) - ScreenLocation;
	ScreenPlayerToMouse.Normalize();

	// Calculate angle in degrees
	MouseAngle = FMath::RadiansToDegrees(FMath::Atan2(ScreenPlayerToMouse.Y, ScreenPlayerToMouse.X));

	//If -180 add 360 so it can go smoothly from 0 to 360
	if (MouseAngle < 0)
	{
		MouseAngle += 360;
	}
	// UE_LOG(LogTemp, Display, TEXT("MouseAngle: %f"), MouseAngle);
}

//This thing will set mouse direction based on angle

void AHero::SetMouseDirectionEnum()
{
	if (!IsDashingCpp)
	{
		for (int i = 0; i < Ranges.Num(); ++i)
		{
			if (MouseAngle >= Ranges[i].Min && MouseAngle < Ranges[i].Max)
			{
				CurrentDirection = StaticCast<EDirections>(i);
				break;
			}
			if (MouseAngle > 310 && MouseAngle < 360)
			{
				CurrentDirection = Right;
			}
		}
		if (SetDirectionBasedOnEnum.Contains(CurrentDirection))
		{
			MouseDirection = SetDirectionBasedOnEnum[CurrentDirection];
		}
	}
}

void AHero::Dash(float DeltaTime)
{
	if (IsDashingCpp)
	{
		StartDashTimer = true;
		DashTimer += DeltaTime;

		if (DashTimer >= 0.97)
		{
			//Revert all the changes to normal
			IsDashingCpp = false;
			HandComponent->SetVisibility(true);
			if (Gun) Gun->FlipBook->SetVisibility(true);
			MovementComponent->MaxSpeed = 200;
		}
	}
	//This is where timer will start
	if (StartDashTimer)
	{
		DashTimer += DeltaTime;
		//Cooldown
		if (DashTimer > 1.2)
		{
			DashTimer = 0;
			StartDashTimer = false;
		}
	}
}


//This is just setting isShooting to false if ShootAction is completed. 
void AHero::SetShootFalse(const FInputActionValue& Value){IsShooting = false;}


//This is for adding input listeners. 
void AHero::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AHero::Move);
		EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Started, this, &AHero::Dash);
		EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Canceled, this, &AHero::SetShootFalse);
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &AHero::Shoot);
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Completed, this, &AHero::Shoot);
	}
}