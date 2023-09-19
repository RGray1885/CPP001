// Trying to make a simple game using c++ and a lot of help

#include "Components/HealthComponent.h"
//#include "GameFramework/Actor.h"
//#include "GameFramework/Pawn.h"
#include "GameFrameWork/Character.h"
#include "Camera/CameraShakeBase.h"
#include "GameFramework/Controller.h"
#include "ShooterGameModeBase.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

/*#include "FireDamageType.h"
#include "IceDamageType.h"
*/



DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All);


// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these
    // features off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;

    // ...
}

void UHealthComponent::OnTakePointDamage(AActor *DamagedActor, float Damage, AController *InstigatedBy,
                                         FVector HitLocation, UPrimitiveComponent *FHitComponent, FName BoneName,
                                         FVector ShotFromDirection, const UDamageType *DamageType, AActor *DamageCauser)
{
    const auto FinalDamage = Damage * GetPointDamageModifier(DamagedActor,BoneName);
    UE_LOG(LogHealthComponent, Display, TEXT("PointDamageTaken %f, final damage: %f, bone: %s"),Damage,FinalDamage,*BoneName.ToString());
    ApplyDamage(FinalDamage, InstigatedBy);
}

void UHealthComponent::OnTakeRadialDamage(AActor *DamagedActor, float Damage, const UDamageType *DamageType,
                                          FVector Origin, const FHitResult &HitInfo, AController *InstigatedBy,
                                          AActor *DamageCauser)
{
    UE_LOG(LogHealthComponent, Display, TEXT("Radial Damage Taken^ %f"),Damage);

    ApplyDamage(Damage, InstigatedBy);
}

void UHealthComponent::OnTakeAnyDamage(AActor *DamagedActor, float Damage, const UDamageType *DamageType,
                                       AController *InstigatedBy, AActor *DamageCauser)
{
    UE_LOG(LogHealthComponent, Display, TEXT("On Any damage taken: %f"), Damage);
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
    Super::BeginPlay();
    check(MaxHealth > 0);
    check(CameraShakeEffect);
    SetHealth(MaxHealth);
    //OnHealthChanged.Broadcast(Health);
    AActor* ComponentOwner = GetOwner();
    if (ComponentOwner)
    {
        ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnTakeAnyDamage);
        ComponentOwner->OnTakePointDamage.AddDynamic(this, &UHealthComponent::OnTakePointDamage);
        ComponentOwner->OnTakeRadialDamage.AddDynamic(this, &UHealthComponent::OnTakeRadialDamage);
    }

    // ...
}

void UHealthComponent::HealFromMedkit(float HealAmount)
{
    //Health = FMath::Clamp((Health + HealAmount),Health,MaxHealth);                  // both works SetHealth(Health + HealAmount);
    SetHealth(Health + HealAmount);
    if (FMath::IsNearlyEqual(Health, MaxHealth, 0))
    {
        bShouldHeal = false;
        GetOwner()->GetWorldTimerManager().ClearTimer(HealTimer);
    }
}

/* void UHealthComponent::DepleteHealth(float Amount)
{
    if (Health > 0.0f)
    {
        Health -= Amount;
    }
}*/


void UHealthComponent::OnHeal()
{
    if (Health < MaxHealth&&bShouldHeal&&IsDead()==false)
    {
        //Health = FMath::Min(Health+HealModifier,MaxHealth);
        SetHealth(Health + HealModifier);
        UE_LOG(LogHealthComponent, Warning, TEXT("Healing in progress"))
        OnHealthChanged.Broadcast(Health);

    }
    else if (FMath::IsNearlyEqual(Health,MaxHealth,0))
    {
        bShouldHeal = false;
        GetOwner()->GetWorldTimerManager().ClearTimer(HealTimer);
        UE_LOG(LogHealthComponent, Warning, TEXT("Healing Complete or player %s is dead"),*GetOwner()->GetName());
    }
}

void UHealthComponent::SetHealth(float NewHealth)
{
    Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
    OnHealthChanged.Broadcast(Health);
}

void UHealthComponent::PlayCameraShake()
{
    if (IsDead())
        return;
    const auto Player = Cast<APawn>(GetOwner());
    if (!Player)
        return;
    const auto Controller = Player->GetController<APlayerController>();
    if (!Controller || !Controller->PlayerCameraManager&&(!CameraShakeEffect))
        return;
    Controller->PlayerCameraManager->StartCameraShake(CameraShakeEffect);
}

void UHealthComponent::Killed(AController *KillerController)
{
    const auto GameMode = Cast<AShooterGameModeBase>(GetWorld()->GetAuthGameMode());
    if (!GameMode)
        return;
    const auto Player = Cast<APawn>(GetOwner());
    const auto VictimController = Player ? Player->Controller : nullptr;
    GameMode->Killed(KillerController,VictimController);
}

void UHealthComponent::ApplyDamage(float Damage, AController *InstigatedBy)
{
    //DepleteHealth(Damage);
    
    if (Damage <= 0.0f || IsDead())
        return;
    // Health = FMath::Clamp(Health - Damage, 0.0f,MaxHealth);
    SetHealth(Health - Damage);

    // OnHealthChanged.Broadcast(Health);
    if (GetOwner()->GetWorldTimerManager().IsTimerActive(HealTimer))
    {
        GetOwner()->GetWorldTimerManager().ClearTimer(HealTimer);
    };
    if (Health < MaxHealth && IsDead() == false)
    {
        // OnHeal();
        bShouldHeal = true;
        GetOwner()->GetWorldTimerManager().SetTimer(HealTimer, this, &UHealthComponent::OnHeal, HealUpdateTime,
                                                    bShouldHeal, HealDelay);
    }

    if (IsDead())
    {
        Killed(InstigatedBy);
        bShouldHeal = false;
        OnDeath.Broadcast();
    }
    UE_LOG(LogHealthComponent, Display, TEXT("Damage: %f"), Damage);
    /* if (DamageType)
    {
        if (DamageType->IsA<UFireDamageType>())
        {
            UE_LOG(LogHealthComponent, Display, TEXT("Fire Damage: %f"), Damage)
        }
        else if (DamageType->IsA<UIceDamageType>())
        {
            UE_LOG(LogHealthComponent, Display, TEXT("Ice Damage: %f"), Damage)
        }
    }*/
    PlayCameraShake();
    OnDamageTaken.Broadcast();
}

float UHealthComponent::GetPointDamageModifier(AActor *DamagedActor, const FName &BoneName)
{
    ACharacter* Character = Cast<ACharacter>(DamagedActor);
    if (!IsValid(Character))
    {
        return 1.f;
    }
    const auto PhysMaterial = Character->GetMesh()->GetBodyInstance(BoneName)->GetSimplePhysicalMaterial();
    if (!DamageModifier.Contains(PhysMaterial))
    {
        return 1.f;
    }
    return DamageModifier[PhysMaterial];
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    // ...
}
