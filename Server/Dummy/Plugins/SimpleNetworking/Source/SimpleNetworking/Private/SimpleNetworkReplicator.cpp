#include "SimpleNetworkReplicator.h"
#include "Logging/LogMacros.h"

DEFINE_LOG_CATEGORY_STATIC(LogSimpleNetworkReplicator, Log, All);

USimpleNetworkReplicator::USimpleNetworkReplicator()
    : LocalClientId(-1)
{
}

void USimpleNetworkReplicator::HandleClientIdPacket(const FClientIdPacket* Packet)
{
    if (!Packet)
        return;

    LocalClientId = Packet->ClientId;
    OnClientIdAssigned.Broadcast(LocalClientId);
}


void USimpleNetworkReplicator::HandleDisconnectPacket(const FDisconnectPacket* Packet)
{
    if (!Packet)
        return;

    OnPlayerDisconnected.Broadcast(Packet->ClientId);
}

void USimpleNetworkReplicator::HandlePositionUpdatePacket(const FPositionUpdatePacket* Packet)
{
    if (!Packet)
        return;

    if (Packet->ClientId == LocalClientId)
    {
        return; // 내 자신의 위치는 무시
    }

    FVector Position(Packet->Position.X, Packet->Position.Y, Packet->Position.Z);
    FVector Velocity(Packet->Velocity.X, Packet->Velocity.Y, Packet->Velocity.Z);

    OnPlayerPositionUpdated.Broadcast(
        Packet->ClientId,
        Position,
        Velocity,
        Packet->State,
        FPlatformTime::Seconds()
    );
}

void USimpleNetworkReplicator::InitializeLocalClientId(int32 InClientId)
{
    LocalClientId = InClientId;
}