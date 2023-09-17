// Trying to make a simple game using c++ and a lot of help


#include "GameInstanceBase.h"
#include "Sound/SoundClass.h"
#include "Sound/SoundFunctionLibrary.h"
void UGameInstanceBase::ToggleVolume()
{
    USoundFunctionLibrary::ToggleSoundClassVolume(MasterSoundClass);
}
