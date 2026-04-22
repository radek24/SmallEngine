//
// Created by radov on 22.04.2026.
//

#pragma once
#include "Engine/Level.h"

class ParticlesLevel : public Level
{
public:
    void OnEnter() override;
    void OnUpdate(float DeltaTime) override;
private:
    void SpawnFirework(const Vector2f& Position);

    TextureHandle ParticleTexture = INVALID_TEXTURE;
};