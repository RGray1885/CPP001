// Trying to make a simple game using c++ and a lot of help


#include "Animations/EquipStartAnimNotify.h"

void UEquipStartAnimNotify::Notify(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation)
{
    OnNotified.Broadcast(MeshComp);
    Super::Notify(MeshComp, Animation);
}
