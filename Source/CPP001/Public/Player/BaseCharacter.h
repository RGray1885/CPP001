// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
//#include "GameFramework/CharacterMovementComponent.h"
//#include "BaseCharMoveComponent.h"
#include "BaseCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UHealthComponent;
class UBaseCharMoveComponent;
class UTextRenderComponent;
class ABaseWeapon;
class UWeaponComponent;


UCLASS()
class CPP001_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
  ABaseCharacter(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Movement")
    bool IsRunning() const;


protected:
	//Add camera to character
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
  UCameraComponent* CameraComponent;
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
  USpringArmComponent* SpringArmComponent;
  UFUNCTION(BlueprintPure, Category = "Movement")
  float GetMovementDirection() const;
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
  UHealthComponent* HealthComponent;
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
  UTextRenderComponent *HealthTextComponent;
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
  UWeaponComponent *WeaponComponent;
  UPROPERTY(EditDefaultsOnly, Category = "Animations")
  UAnimMontage *DeathAnimMontage;
  UPROPERTY(EditDefaultsOnly, Category = "Movement")
  FVector2D LandedDamageVelocity=FVector2D(900.0f, 1200.0f); 
  UPROPERTY(EditDefaultsOnly, Category = "Movement")
  FVector2D LandedDamage = FVector2D(10.0f, 100.0f);
  UPROPERTY(EditDefaultsOnly, Category = "Damage")
  float LifeSpanOnDeath = 5.0f;
  
  
private:
	  //MovementControl
    void MoveForward(float Amount);
    void MoveRight(float Amount);
    void OnSprint();
    void StopSprint();
    UCharacterMovementComponent *CharacterMovement = GetCharacterMovement();
    bool bIsMovingForward;
    bool bIsMovingSideways;
    bool bShouldRun = false;
    void OnDeath();
    void OnHealthChanged(float Health);
    UFUNCTION()
	void OnGroundLanded(const FHitResult& Hit);
public:
    bool GetIsRunning()
    {
        return bShouldRun;
    }
    UWeaponComponent* GetWeaponComponent() const
    {
            return WeaponComponent;
    }
	
};
