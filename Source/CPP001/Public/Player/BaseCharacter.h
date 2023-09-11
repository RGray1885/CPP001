// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
//#include "GameFramework/CharacterMovementComponent.h"
//#include "BaseCharMoveComponent.h"
#include "BaseCharacter.generated.h"


class UHealthComponent;
class UBaseCharMoveComponent;
class ABaseWeapon;
class UWeaponComponent;


UCLASS()
class CPP001_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
  ABaseCharacter(const FObjectInitializer& ObjInit);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    virtual void OnDeath();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input

	UFUNCTION(BlueprintCallable, Category = "Movement")
    virtual bool IsRunning() const;


protected:
	//Add camera to character
  //UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
  //UCameraComponent* CameraComponent;
  //UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
  //USpringArmComponent* SpringArmComponent;
  UFUNCTION(BlueprintPure, Category = "Movement")
  float GetMovementDirection() const;
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
  UHealthComponent* HealthComponent;
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
  UPROPERTY(EditDefaultsOnly, Category = "Materials")
  FName MaterialColorName = "Paint Color";

 virtual void OnHealthChanged(float Health);

  


  
private:
	  //MovementControl
    //void MoveForward(float Amount);
    //void MoveRight(float Amount);
    //void OnSprint();
    //void StopSprint();
    UCharacterMovementComponent *CharacterMovement = GetCharacterMovement();
    
  protected:
    bool bShouldRun = false;
    bool bIsMovingForward;
    bool bIsMovingSideways;
  private:
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
    void SetPlayerColor(const FLinearColor &Color);
};
