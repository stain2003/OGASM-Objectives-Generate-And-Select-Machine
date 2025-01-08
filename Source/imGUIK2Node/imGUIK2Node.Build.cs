using UnrealBuildTool;

public class imGUIK2Node : ModuleRules
{
    public imGUIK2Node(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "BlueprintGraph",
                "KismetCompiler",
                "GraphEditor",
                "UnrealEd",
                "ImGui",
                "OGASM"
            }
        );
    }
}