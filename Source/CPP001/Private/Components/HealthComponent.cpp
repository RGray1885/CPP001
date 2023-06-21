// Trying to make a simple game using c++ and a lot of help

#include "Components/HealthComponent.h"
#include "GameFramework/Actor.h"
#include "FireDamageType.h"
#include "IceDamageType.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent,All,All)


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
    Health = MaxHealth;
    AActor* ComponentOwner = GetOwner();
    if (ComponentOwner)
    {
        ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnTakeAnyDamage);
    }

    // ...
}

void UHealthComponent::DepleteHealth(float Amount)
{
    if (Health > 0.0f)
    {
        Health -= Amount;
    }
}
void UHealthComponent::OnTakeAnyDamage(AActor *DamagedActor, float Damage, const UDamageType *DamageType,
                                           AController *InstigatedBy, AActor *DamageCauser)
{
    //DepleteHealth(Damage);
    Health -= Damage;
    UE_LOG(LogHealthComponent, Display, TEXT("Damage: %f"),Damage);
    if (DamageType)
    {
        if (DamageType->IsA<UFireDamageType>())
        {
            UE_LOG(LogHealthComponent, Display, TEXT("Fire Damage: %f"), Damage)
        }
        else if (DamageType->IsA<UIceDamageType>())
        {
            UE_LOG(LogHealthComponent, Display, TEXT("Ice Damage: %f"), Damage)
        }
    }
}

// Called every frame
/* void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    //DepleteHealth(0.1);
    // ...
}*/
