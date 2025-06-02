#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
#include "HeightmapExporter.generated.h"

UCLASS(BlueprintType, Blueprintable)
class MW_API UHeightmapExporter : public UEditorUtilityWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Heightmap Export")
    void ExportLandscapeHeightmap();
};