// Trying to make a simple game using c++ and a lot of help

#include "Weapon/ProjectileRocket.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Weapon/Components/WeaponFXComponent.h"

// Sets default values
AProjectileRocket::AProjectileRocket()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    CollisionComponent->InitSphereRadius(5.0f);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
    CollisionComponent->bReturnMaterialOnMove = true;
    SetRootComponent(CollisionComponent);

    ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
    ProjectileMovementComponent->InitialSpeed = 1500.0f;
    ProjectileMovementComponent->ProjectileGravityScale = 0.1f;

    WeaponFXComponent = CreateDefaultSubobject<UWeaponFXComponent>("WeaponFXComponent");
}

// Called when the game starts or when spawned
void AProjectileRocket::BeginPlay()
{
    Super::BeginPlay();

    check(ProjectileMovementComponent);
    check(CollisionComponent);
    check(WeaponFXComponent);

    ProjectileMovementComponent->Velocity = ShotDirection * ProjectileMovementComponent->InitialSpeed;
    CollisionComponent->IgnoreActorWhenMoving(GetOwner(), true);
    CollisionComponent->OnComponentHit.AddDynamic(this, &AProjectileRocket::OnProjectileHit);
    SetLifeSpan(ProjectileLifeSpan);
}

void AProjectileRocket::OnProjectileHit(UPrimitiveComponent *HitComponent, AActor *OtherActor,
                                        UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit)
{
    if (!GetWorld())
        return;
    ProjectileMovementComponent->StopMovementImmediately();
    DrawDebugSphere(GetWorld(), GetActorLocation(), DamageRadius, 32, FColor::Black, false, 5.0f);
    WeaponFXComponent->PlayImpactFX(Hit);
    UGameplayStatics::ApplyRadialDamage(GetWorld(),                 //
                                        DamageToDeal,               //
                                        GetActorLocation(),         //
                                        DamageRadius,               //
                                        UDamageType::StaticClass(), //
                                        {GetController()},          //
                                        this,                       //
                                        GetController(),            //
                                        DoFullDamage);

    // make damage

    Destroy();
}

AController *AProjectileRocket::GetController() const
{
    const auto Pawn=Cast<APawn>(GetOwner());
    return Pawn? Pawn->GetController():nullptr;
}
