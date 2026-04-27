#pragma once

struct PlayerShipComponent
{
    int Lives = 3;
    int Score = 0;
    float FireCooldown = 0.0f;
    bool IsDead = false;
    float RespawnTimer = 0.0f;
    bool IsInvincible = false;
    float InvincibleTimer = 0.0f;
    bool ShipVisible = true;
    bool IsThrustHeld = false;
};