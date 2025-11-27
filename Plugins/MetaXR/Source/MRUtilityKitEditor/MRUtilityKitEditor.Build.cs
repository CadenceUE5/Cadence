// Copyright (c) Meta Platforms, Inc. and affiliates.

using UnrealBuildTool;

public class MRUtilityKitEditor : ModuleRules
{
    public MRUtilityKitEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        bUsePrecompiled = true;
        bUseUnity = true;

        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
            });


        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "OculusXRHMD",
                "OculusXRAnchors",
                "OculusXRScene",
                "Json",
                "UnrealEd",
                "RHI",
                "RenderCore",
                "ProceduralMeshComponent",
                "MRUtilityKit",
            });
    }
}
