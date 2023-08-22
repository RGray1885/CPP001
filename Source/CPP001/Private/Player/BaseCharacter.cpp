// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/BaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/BaseCharMoveComponent.h"
#include "Components/InputComponent.h"
#include "Components/HealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Controller.h"
#include "Weapon/BaseWeapon.h"
#include "Components/WeaponComponent.h"
#include "Components/CapsuleComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseCharacter, All, All);


// Sets default values
ABaseCharacter::ABaseCharacter(const FObjectInitializer &ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass<UBaseCharMoveComponent>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Set and attach camera
    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = true;
    SpringArmComponent->bEnableCameraLag = true;
    SpringArmComponent->TargetArmLength = 220.0f;
    SpringArmComponent->SocketOffset = FVector(0.0f,100.0f,110.0f);
    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);
    HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");
    HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent");
    HealthTextComponent->SetupAttachment(GetRootComponent());
    HealthTextComponent->SetOwnerNoSee(true);
    WeaponComponent = CreateDefaultSubobject<UWeaponComponent>("WeaponControlComponent");
}



// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
    check(HealthComponent);
    check(HealthTextComponent);
    check(GetCharacterMovement());
    check(GetMesh());
    HealthComponent->OnDeath.AddUObject(this, &ABaseCharacter::OnDeath);
    HealthComponent->OnHealthChanged.AddUObject(this, &ABaseCharacter::OnHealthChanged);
    OnHealthChanged(HealthComponent->GetHealth());
    LandedDelegate.AddDynamic(this, &ABaseCharacter::OnGroundLanded);
   

}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
   
}


// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    check(PlayerInputComponent);
    PlayerInputComponent->BindAxis("MoveForward", this, &ABaseCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ABaseCharacter::MoveRight);
    PlayerInputComponent->BindAxis("LookUp", this, &ABaseCharacter::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("LookAround", this, &ABaseCharacter::AddControllerYawInput);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ABaseCharacter::Jump);
    PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ABaseCharacter::OnSprint);
    PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ABaseCharacter::StopSprint);
    PlayerInputComponent->BindAction("FireWeapon", IE_Pressed, WeaponComponent, &UWeaponComponent::FireWeapon);
    PlayerInputComponent->BindAction("FireWeapon", IE_Released, WeaponComponent, &UWeaponComponent::StopFiring);
    PlayerInputComponent->BindAction("SwitchWeapon", IE_Pressed, WeaponComponent, &UWeaponComponent::NextWeapon);
    PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &UWeaponComponent::Reload);

}

bool ABaseCharacter::IsRunning() const
{
    return bShouldRun && bIsMovingForward && !bIsMovingSideways && !GetVelocity().IsZero();
}

float ABaseCharacter::GetMovementDirection() const
{
    if (GetVelocity().IsZero())
    return 0.0f;
    const auto VelocityNormal = GetVelocity().GetSafeNormal();
    const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
    const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
    const auto Degrees = FMath::RadiansToDegrees(AngleBetween);
    return CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
}

void ABaseCharacter::MoveForward(float Amount)
{
    bIsMovingForward = Amount > 0.0f;
    if (Amount == 0.0f)
        return;
    AddMovementInput(GetActorForwardVector(), Amount);
}

void ABaseCharacter::MoveRight(float Amount)
{
    bIsMovingSideways = Amount != 0.0f;
    if (Amount == 0.0f)
        return;
    AddMovementInput(GetActorRightVector(), Amount);
}

void ABaseCharacter::OnSprint()
{
    if (WeaponComponent->GetIsFiring())
        return;
    bShouldRun = true;
}

void ABaseCharacter::StopSprint()
{
    bShouldRun = false;
}

void ABaseCharacter::OnDeath()
{
    UE_LOG(LogBaseCharacter, Warning, TEXT("Player %s is dead"), *GetName());
    //PlayAnimMontage(DeathAnimMontage);

    GetCharacterMovement()->DisableMovement();
    SetLifeSpan(LifeSpanOnDeath);
    GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    HealthTextComponent->SetHiddenInGame(true);
    WeaponComponent->StopFiring();
    if (Controller)
    {
        Controller->ChangeState(NAME_Spectating);
    }
    GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    GetMesh()->SetSimulatePhysics(true);
    
}

void ABaseCharacter::OnHealthChanged(float Health)
{
    HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("% .0f"), Health)));
}

void ABaseCharacter::OnGroundLanded(const FHitResult &Hit)
{
    const auto FallVelocityZ = -GetCharacterMovement()->Velocity.Z;
    UE_LOG(LogBaseCharacter, Display, TEXT("OnLanded: %f"), FallVelocityZ);
    if (FallVelocityZ < LandedDamageVelocity.X)
        return;
    const auto FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallVelocityZ);
    TakeDamage(FinalDamage, FDamageEvent{}, nullptr, nullptr);
    UE_LOG(LogBaseCharacter, Display, TEXT("Final Damage: %f"), FinalDamage);
}

void ABaseCharacter::SetPlayerColor(const FLinearColor &Color)
{
    const auto MaterialInstance = GetMesh()->CreateAndSetMaterialInstanceDynamic(0);
    if (!MaterialInstance)
        return;
    MaterialInstance->SetVectorParameterValue(MaterialColorName, Color);
}

