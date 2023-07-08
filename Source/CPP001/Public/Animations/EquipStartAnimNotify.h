// Trying to make a simple game using c++ and a lot of help

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EquipStartAnimNotify.generated.h"
DECLARE_MULTICAST_DELEGATE_OneParam(FOnNotifiedSignature, USkeletalMeshComponent *);

/**
 * 
 */
UCLASS()
class CPP001_API UEquipStartAnimNotify : public UAnimNotify
{
	GENERATED_BODY()
    public:
        virtual void Notify(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation) override;
    FOnNotifiedSignature OnNotified;
};