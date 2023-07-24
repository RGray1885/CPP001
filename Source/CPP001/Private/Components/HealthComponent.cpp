// Trying to make a simple game using c++ and a lot of help

#include "Components/HealthComponent.h"
#include "GameFramework/Actor.h"
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

// Called when the game starts
void UHealthComponent::BeginPlay()
{
    Super::BeginPlay();
    check(MaxHealth > 0);
    SetHealth(MaxHealth);
    //OnHealthChanged.Broadcast(Health);
    AActor* ComponentOwner = GetOwner();
    if (ComponentOwner)
    {
        ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnTakeAnyDamage);
    }

    // ...
}

void UHealthComponent::HealFromMedkit(float HealAmount)
{
    Health = FMath::Clamp((Health + HealAmount),Health,MaxHealth);                  // both works SetHealth(Health + HealAmount);
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
void UHealthComponent::OnTakeAnyDamage(AActor *DamagedActor, float Damage, const UDamageType *DamageType,
                                           AController *InstigatedBy, AActor *DamageCauser)
{
    //DepleteHealth(Damage);
    
    if (Damage<=0.0f || IsDead())
        return;
    //Health = FMath::Clamp(Health - Damage, 0.0f,MaxHealth);
    SetHealth(Health - Damage);
    //OnHealthChanged.Broadcast(Health);
    if (GetOwner()->GetWorldTimerManager().IsTimerActive(HealTimer))
    {
        GetOwner()->GetWorldTimerManager().ClearTimer(HealTimer);

    };
    if (Health < MaxHealth && IsDead()==false)
    {
        //OnHeal(); 
         bShouldHeal = true;
        GetOwner()->GetWorldTimerManager().SetTimer(HealTimer,this,&UHealthComponent::OnHeal,HealUpdateTime,bShouldHeal,HealDelay);
    }

    if (IsDead())
    {
        bShouldHeal = false;
        OnDeath.Broadcast();
    }
    UE_LOG(LogHealthComponent, Display, TEXT("Damage: %f"),Damage);
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
}

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

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    // ...
}
