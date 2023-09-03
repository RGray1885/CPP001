// Trying to make a simple game using c++ and a lot of help


#include "Player/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "Components/WeaponComponent.h"


//#include "Components/BaseCharMoveComponent.h"

APlayerCharacter::APlayerCharacter(const FObjectInitializer &ObjInit) : Super(ObjInit)
{
    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = true;
    SpringArmComponent->bEnableCameraLag = true;
    SpringArmComponent->TargetArmLength = 220.0f;
    SpringArmComponent->SocketOffset = FVector(0.0f, 100.0f, 110.0f);
    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);
   
}
void APlayerCharacter::OnDeath()
{
    Super::OnDeath();
    if (Controller)
    {
        Controller->ChangeState(NAME_Spectating);
    }
    
}
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    check(PlayerInputComponent);
    PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
    PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("LookAround", this, &APlayerCharacter::AddControllerYawInput);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::Jump);
    PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &APlayerCharacter::OnSprint);
    PlayerInputComponent->BindAction("Sprint", IE_Released, this, &APlayerCharacter::StopSprint);
    PlayerInputComponent->BindAction("FireWeapon", IE_Pressed, WeaponComponent, &UWeaponComponent::FireWeapon);
    PlayerInputComponent->BindAction("FireWeapon", IE_Released, WeaponComponent, &UWeaponComponent::StopFiring);
    PlayerInputComponent->BindAction("SwitchWeapon", IE_Pressed, WeaponComponent, &UWeaponComponent::NextWeapon);
    PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &UWeaponComponent::Reload);
}
bool APlayerCharacter::IsRunning() const
{
    return bShouldRun && bIsMovingForward && !bIsMovingSideways && !GetVelocity().IsZero();
}
void APlayerCharacter::MoveForward(float Amount)
{
    bIsMovingForward = Amount > 0.0f;
    if (Amount == 0.0f)
        return;
    AddMovementInput(GetActorForwardVector(), Amount);
}

void APlayerCharacter::MoveRight(float Amount)
{
    bIsMovingSideways = Amount != 0.0f;
    if (Amount == 0.0f)
        return;
    AddMovementInput(GetActorRightVector(), Amount);
}

void APlayerCharacter::OnSprint()
{
    if (WeaponComponent->GetIsFiring())
        return;
    bShouldRun = true;
}

void APlayerCharacter::StopSprint()
{
    bShouldRun = false;
}