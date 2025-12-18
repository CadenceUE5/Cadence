#pragma once

#include "CoreMinimal.h"

/* Non-Unreal Ecosystem C++ Macros and Utitities */

DECLARE_LOG_CATEGORY_EXTERN(LogCadence, Log, All);

#if !UE_BUILD_SHIPPING

#ifdef __INTELLISENSE__
#define GENERATED_BODY()  // Intellisense does not like GENERATED_BODY for some reason
#endif

/* Print to screen is very exhausting */
#define K8_SCREEN(MSG, ...)                                                                        \
    if (GEngine)                                                                                   \
    GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow,                                      \
                                     FString::Printf(TEXT(MSG), ##__VA_ARGS__))

#define K8_LOG(Verbosity, Message, ...)                                                            \
    UE_LOG(LogCadence, Verbosity, TEXT("[%s] " Message), TEXT(__FUNCTION__), ##__VA_ARGS__)

#else
// strip in shipping builds, will not pollute global namespace
#define K8_SCREEN(...)
#define K8_LOG(...)

#endif

#if defined(__INTELLISENSE__)
#define K8_GENERATED_FUNCTION_SOURCE(FuncName, ReturnType, Args) ReturnType FuncName Args
#else
#define K8_GENERATED_FUNCTION_SOURCE(FuncName, ReturnType, Args)                                   \
    ReturnType FuncName##_Implementation Args
#endif

namespace K8::Utility
{
// Unused for now
}
