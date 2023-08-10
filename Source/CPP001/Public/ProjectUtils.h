#pragma once
class ProjectUtils
{
  public:
    template <typename T> static T *GetPlayerComponent(AActor *PlayerPawn)
    {
        if (!PlayerPawn)
            return nullptr;
        const auto Component = PlayerPawn->GetComponentByClass(T::StaticClass());
        return Cast<T>(Component);
    }
};