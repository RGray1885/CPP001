// Trying to make a simple game using c++ and a lot of help


#include "Sound/SoundFunctionLibrary.h"
#include "Sound/SoundClass.h"


DEFINE_LOG_CATEGORY_STATIC(LogSoundFunctionLibrary,All,All)
void USoundFunctionLibrary::SetSoundClassVolume(USoundClass *SoundClass, float Volume)
{
    if (!IsValid(SoundClass))
    {
        return;
    }
    else
    {
        SoundClass->Properties.Volume = FMath::Clamp(Volume,0.f,1.f);
        UE_LOG(LogSoundFunctionLibrary, Display, TEXT("Volume in %s changed to %f"), *SoundClass->GetName(), SoundClass->Properties.Volume);
    }
}

void USoundFunctionLibrary::ToggleSoundClassVolume(USoundClass *SoundClass)
{
    if (!IsValid(SoundClass))
    {
        return;
    }
    else
    {
        const float NextVolume = SoundClass->Properties.Volume > 0.f ? 0.f : 1.f;
        SetSoundClassVolume(SoundClass, NextVolume);
    }

}
