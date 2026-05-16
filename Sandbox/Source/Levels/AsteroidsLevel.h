#pragma once
#include <optional>
#include "Engine/Level.h"
#include "Engine/Rendering/TextureManager.h"
#include "Engine/Signals/SignalManager.h"

class AsteroidsLevel : public Level
{
public:
    void OnEnter() override;
    void OnExit()  override;

private:
    TextureHandle ParticleTexture = INVALID_TEXTURE;

    std::optional<Entity> ScoreTextEntity;
    std::optional<Entity> LivesTextEntity;

    SubscriptionId ScoreSubId = 0;
    SubscriptionId LivesSubId = 0;
};
