using UnrealBuildTool;

public class CadenceEditor: ModuleRules
{
    public CadenceEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PrivateDependencyModuleNames.AddRange(new string[] {            
            "Cadence",
            "Core",
            "CoreUObject",
            "Engine",
            "UnrealEd",
            "Slate",
            "SlateCore",
            "EditorFramework",
            "RenderCore"
        });
    }
}
