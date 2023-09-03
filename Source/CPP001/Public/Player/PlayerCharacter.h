// Trying to make a simple game using c++ and a lot of help

#pragma once

#include "CoreMinimal.h"
#include "Player/BaseCharacter.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */

class UCameraComponent;
class USpringArmComponent;
class USphereComponent;
class UCapsuleComponent;


UCLASS()
class CPP001_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()
  public:
    APlayerCharacter(const FObjectInitializer &ObjInit);

	protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UCameraComponent *CameraComponent;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USpringArmComponent *SpringArmComponent;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USphereComponent *CameraCollisionComponent;

    protected:
    virtual void OnDeath() override;
      virtual void BeginPlay() override;

    public:
    virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

    virtual bool IsRunning() const override;

    private:
    void MoveForward(float Amount);
    void MoveRight(float Amount);
    void OnSprint();
    void StopSprint();
    UCharacterMovementComponent *CharacterMovement = GetCharacterMovement();
    


    UFUNCTION()
    void OnCameraCollisionBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
                                       UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                       const FHitResult &SweepResult);
   

    UFUNCTION()
    void OnCameraCollisionEndOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
                                     UPrimitiveComponent *OtherComp, int32 OtherBodyIndex);
   
    void CheckCameraOverlap();
};
