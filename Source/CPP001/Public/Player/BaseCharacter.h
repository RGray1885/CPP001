// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BaseCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class CPP001_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


protected:
	//Add camera to character
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
  UCameraComponent* CameraComponent;
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
  USpringArmComponent *SpringArmComponent;
  UFUNCTION(BlueprintPure, Category = "Movement")
  float GetMovementDirection() const;

  private:
	  //MovementControl
    void MoveForward(float Amount);
    void MoveRight(float Amount);
    void OnSprint();
    void StopSprint();
    UCharacterMovementComponent *CharacterMovement = GetCharacterMovement();
    bool bIsMovingForward;
    bool bIsMovingSideways;
};
