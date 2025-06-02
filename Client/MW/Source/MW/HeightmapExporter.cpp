#include "HeightmapExporter.h"

#include "Landscape.h"
#include "LandscapeInfo.h"
#include "LandscapeComponent.h"
#include "Engine/World.h"
#include "Editor.h"
#include "Misc/FileHelper.h"
#include "HAL/PlatformFilemanager.h"
#include "EngineUtils.h"
#include "Engine/Texture2D.h"
#include "Engine/TextureRenderTarget2D.h"

void UHeightmapExporter::ExportLandscapeHeightmap()
{
    UE_LOG(LogTemp, Warning, TEXT("=== Starting Heightmap Export ==="));

    // Get current editor world
    UWorld* World = GEditor->GetEditorWorldContext().World();
    if (!World)
    {
        UE_LOG(LogTemp, Error, TEXT("Cannot find world!"));
        return;
    }

    // Find Landscape
    ALandscape* Landscape = nullptr;
    for (TActorIterator<ALandscape> ActorItr(World); ActorItr; ++ActorItr)
    {
        Landscape = *ActorItr;
        UE_LOG(LogTemp, Warning, TEXT("Landscape found: %s"), *Landscape->GetName());
        break;
    }

    if (!Landscape)
    {
        UE_LOG(LogTemp, Error, TEXT("No Landscape found in the map! Please check if Landscape exists."));
        return;
    }

    // Get LandscapeInfo
    ULandscapeInfo* LandscapeInfo = Landscape->GetLandscapeInfo();
    if (!LandscapeInfo)
    {
        UE_LOG(LogTemp, Error, TEXT("Cannot get LandscapeInfo!"));
        return;
    }

    // Get all landscape components
    TSet<ULandscapeComponent*> LandscapeComponents;
    LandscapeInfo->ForAllLandscapeComponents([&LandscapeComponents](ULandscapeComponent* Component)
        {
            if (Component)
            {
                LandscapeComponents.Add(Component);
            }
        });

    if (LandscapeComponents.Num() == 0)
    {
        UE_LOG(LogTemp, Error, TEXT("No landscape components found!"));
        return;
    }

    UE_LOG(LogTemp, Warning, TEXT("Found %d landscape components"), LandscapeComponents.Num());

    // Find bounds by examining components
    int32 MinX = INT32_MAX, MinY = INT32_MAX;
    int32 MaxX = INT32_MIN, MaxY = INT32_MIN;

    for (ULandscapeComponent* Component : LandscapeComponents)
    {
        FIntPoint ComponentKey = Component->GetSectionBase() / Component->ComponentSizeQuads;
        MinX = FMath::Min(MinX, ComponentKey.X);
        MinY = FMath::Min(MinY, ComponentKey.Y);
        MaxX = FMath::Max(MaxX, ComponentKey.X);
        MaxY = FMath::Max(MaxY, ComponentKey.Y);
    }

    int32 ComponentSizeQuads = Landscape->ComponentSizeQuads;
    int32 ComponentCountX = MaxX - MinX + 1;
    int32 ComponentCountY = MaxY - MinY + 1;

    int32 Width = ComponentCountX * ComponentSizeQuads + 1;
    int32 Height = ComponentCountY * ComponentSizeQuads + 1;

    UE_LOG(LogTemp, Warning, TEXT("Landscape size: %d x %d"), Width, Height);
    UE_LOG(LogTemp, Warning, TEXT("Component counts: %d x %d"), ComponentCountX, ComponentCountY);
    UE_LOG(LogTemp, Warning, TEXT("Component size: %d quads"), ComponentSizeQuads);

    // Create a map for quick component lookup
    TMap<FIntPoint, ULandscapeComponent*> ComponentMap;
    for (ULandscapeComponent* Component : LandscapeComponents)
    {
        FIntPoint ComponentKey = Component->GetSectionBase() / Component->ComponentSizeQuads;
        ComponentMap.Add(ComponentKey, Component);
    }

    // Prepare height data array
    TArray<uint16> HeightData;
    HeightData.SetNumZeroed(Width * Height);

    UE_LOG(LogTemp, Warning, TEXT("Extracting height data..."));

    // Process each component
    int32 ProcessedComponents = 0;
    for (int32 ComponentY = MinY; ComponentY <= MaxY; ComponentY++)
    {
        for (int32 ComponentX = MinX; ComponentX <= MaxX; ComponentX++)
        {
            FIntPoint ComponentKey(ComponentX, ComponentY);
            ULandscapeComponent* Component = ComponentMap.FindRef(ComponentKey);

            if (!Component)
            {
                UE_LOG(LogTemp, Warning, TEXT("Component not found at (%d, %d)"), ComponentX, ComponentY);
                continue;
            }

            // Get heightmap texture from component
            UTexture2D* HeightmapTexture = Component->GetHeightmap();
            if (!HeightmapTexture)
            {
                UE_LOG(LogTemp, Warning, TEXT("No heightmap texture in component (%d, %d)"), ComponentX, ComponentY);
                continue;
            }

            // Read texture data (simplified approach for UE 5.5)
            // This approach uses Line Trace as fallback
            int32 LocalComponentX = ComponentX - MinX;
            int32 LocalComponentY = ComponentY - MinY;

            // Sample heights using line trace for this component area
            for (int32 Y = 0; Y <= ComponentSizeQuads; Y++)
            {
                for (int32 X = 0; X <= ComponentSizeQuads; X++)
                {
                    // Calculate world position
                    FVector ComponentLocation = Component->GetComponentLocation();
                    FVector ComponentScale = Component->GetComponentScale();

                    float WorldX = ComponentLocation.X + (X - ComponentSizeQuads * 0.5f) * ComponentScale.X;
                    float WorldY = ComponentLocation.Y + (Y - ComponentSizeQuads * 0.5f) * ComponentScale.Y;

                    // Line trace to get height
                    FVector TraceStart(WorldX, WorldY, 10000.0f);
                    FVector TraceEnd(WorldX, WorldY, -10000.0f);

                    FHitResult HitResult;
                    FCollisionQueryParams QueryParams;
                    QueryParams.bTraceComplex = false;
                    QueryParams.AddIgnoredActor(Landscape);

                    float HeightValue = 0.0f;
                    if (World->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_WorldStatic, QueryParams))
                    {
                        HeightValue = HitResult.Location.Z;
                    }
                    else
                    {
                        // Use component location as fallback
                        HeightValue = ComponentLocation.Z;
                    }

                    // Convert to uint16 and store
                    int32 GlobalX = LocalComponentX * ComponentSizeQuads + X;
                    int32 GlobalY = LocalComponentY * ComponentSizeQuads + Y;
                    int32 GlobalIndex = GlobalY * Width + GlobalX;

                    if (GlobalIndex >= 0 && GlobalIndex < HeightData.Num())
                    {
                        // Convert height to uint16 (assuming height range -512 to 512)
                        uint16 QuantizedHeight = static_cast<uint16>(FMath::Clamp(
                            (HeightValue + 512.0f) / 1024.0f * 65535.0f, 0.0f, 65535.0f));
                        HeightData[GlobalIndex] = QuantizedHeight;
                    }
                }
            }

            ProcessedComponents++;
            if (ProcessedComponents % 5 == 0)
            {
                UE_LOG(LogTemp, Warning, TEXT("Processed %d/%d components"), ProcessedComponents, ComponentCountX * ComponentCountY);
            }
        }
    }

    UE_LOG(LogTemp, Warning, TEXT("Processed %d components"), ProcessedComponents);

    // Calculate world coordinate info
    FVector LandscapeScale = Landscape->GetActorScale3D();
    FVector LandscapeLocation = Landscape->GetActorLocation();

    // Calculate world bounds
    float WorldMinX = LandscapeLocation.X + MinX * ComponentSizeQuads * LandscapeScale.X;
    float WorldMinY = LandscapeLocation.Y + MinY * ComponentSizeQuads * LandscapeScale.Y;
    float WorldMaxX = LandscapeLocation.X + (MaxX + 1) * ComponentSizeQuads * LandscapeScale.X;
    float WorldMaxY = LandscapeLocation.Y + (MaxY + 1) * ComponentSizeQuads * LandscapeScale.Y;

    UE_LOG(LogTemp, Warning, TEXT("World coordinate range:"));
    UE_LOG(LogTemp, Warning, TEXT("X: %.2f ~ %.2f"), WorldMinX, WorldMaxX);
    UE_LOG(LogTemp, Warning, TEXT("Y: %.2f ~ %.2f"), WorldMinY, WorldMaxY);
    UE_LOG(LogTemp, Warning, TEXT("Z scale: %.2f"), LandscapeScale.Z);

    // Set save folder path
    FString ProjectDir = FPaths::ProjectDir();
    FString ServerDir = ProjectDir + TEXT("Map/");
    FString HeightmapPath = ServerDir + TEXT("heightmap.bin");
    FString MetaPath = ServerDir + TEXT("heightmap_meta.txt");

    UE_LOG(LogTemp, Warning, TEXT("Save path: %s"), *ServerDir);

    // Create Server folder if it doesn't exist
    IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
    if (!PlatformFile.DirectoryExists(*ServerDir))
    {
        if (PlatformFile.CreateDirectory(*ServerDir))
        {
            UE_LOG(LogTemp, Warning, TEXT("Server folder created"));
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to create Server folder!"));
            return;
        }
    }

    // Convert height data to byte array
    TArray<uint8> ByteData;
    ByteData.SetNum(HeightData.Num() * sizeof(uint16));
    FMemory::Memcpy(ByteData.GetData(), HeightData.GetData(), ByteData.Num());

    // Save heightmap binary file
    if (FFileHelper::SaveArrayToFile(ByteData, *HeightmapPath))
    {
        UE_LOG(LogTemp, Warning, TEXT("Heightmap data saved successfully: %s"), *HeightmapPath);
        UE_LOG(LogTemp, Warning, TEXT("Data size: %d bytes (%d height values)"), ByteData.Num(), HeightData.Num());
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to save heightmap data!"));
        return;
    }

    // Generate metadata (width,height,minX,minY,maxX,maxY,zScale,zOffset)
    FString MetaData = FString::Printf(
        TEXT("%d,%d,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f"),
        Width, Height,
        WorldMinX, WorldMinY, WorldMaxX, WorldMaxY,
        LandscapeScale.Z, LandscapeLocation.Z
    );

    // Save metadata file
    if (FFileHelper::SaveStringToFile(MetaData, *MetaPath))
    {
        UE_LOG(LogTemp, Warning, TEXT("Metadata saved successfully: %s"), *MetaPath);
        UE_LOG(LogTemp, Warning, TEXT("Metadata content: %s"), *MetaData);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to save metadata!"));
        return;
    }

    UE_LOG(LogTemp, Warning, TEXT("=== Heightmap Export Complete! ==="));
    UE_LOG(LogTemp, Warning, TEXT("File location: %s"), *ServerDir);
}