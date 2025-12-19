#include "Cadence/K8_DeveloperSettings.h"

UK8_WorldSubsystemSettingsDataAsset* UK8_DeveloperSettings::GetDefaultWorldSubsystemSettings()
{
    UK8_WorldSubsystemSettingsDataAsset* Settings = GetDefault<UK8_DeveloperSettings>()
                                                        ->WorldSubsystemSettings.LoadSynchronous();

    if (!Settings)
    {
        K8_LOG(
            Log,
            "World settings could not be loaded from developer settings. Falling back to asset registry.");

        Settings = K8::Utility::TryFindAsset<UK8_WorldSubsystemSettingsDataAsset>();
    }

    if (!Settings)
    {
        K8_LOG(Error, "World settings could not be located within project. Subsystem disabled.");
        return nullptr;
    }

    return Settings;
}
