// Trying to make a simple game using c++ and a lot of help


#include "Weapon/BaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "BaseWeapon.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All);
// Sets default values
ABaseWeapon::ABaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
    SetRootComponent(WeaponMesh);
}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
    check(WeaponMesh);
	
}

void ABaseWeapon::Fire()
{
    UE_LOG(LogBaseWeapon, Warning, TEXT("Fire!"));
    MakeShot();
}

void ABaseWeapon::MakeShot()
{
    if(!GetWorld()) return;

    const auto Player = Cast<ACharacter>(GetOwner());
    if (!Player)
        return;
    const auto Controller = Player->GetController<APlayerController>();
    if (!Controller)
        return;
    FVector ViewLocation;
    FRotator ViewRotation;
    Controller->GetPlayerViewPoint(ViewLocation,ViewRotation);

    const FTransform SocketTransform = WeaponMesh->GetSocketTransform(MuzzleSocketName);
    const FVector TraceStart = ViewLocation; // SocketTransform.GetLocation();
    const FVector ShootDirection = ViewRotation.Vector();
    //SocketTransform.GetRotation().GetForwardVector();
    const FVector TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;

    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(GetOwner());

    FHitResult HitResult;
    GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility);

    if(HitResult.bBlockingHit)
    {
        DrawDebugLine(GetWorld(), SocketTransform.GetLocation(), HitResult.ImpactPoint, FColor::Green, false, 3.0f, 0, 3);

        DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 20.0f, 32, FColor::Red, false, 3.0f, 0, 3);
        UE_LOG(LogBaseWeapon, Display, TEXT("Bone: %s"), *HitResult.BoneName.ToString());
    }
    else
    {
        DrawDebugLine(GetWorld(), SocketTransform.GetLocation(), TraceEnd, FColor::Red, false, 3.0f, 0, 3);

    }
}


