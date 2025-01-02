#include "ComponentNode.h"

#include "ComponentMusic.h"
#include "picojson.h"
#include "Engine/MyEngine.h"
#include "Engine/Components/ComponentRendererSprite.h"
#include "glm/gtc/constants.hpp"

void ComponentNode::Init(rapidjson::Value& serializedData)
{
	startTime = std::chrono::steady_clock::now();
}

void ComponentNode::Update(float delta)
{
    auto gameObject = GetGameObject().lock()->FindComponent<ComponentRendererSprite>().lock();
    auto music = MyEngine::Engine::GetInstance()->GetGameObject("root").lock();
    auto musicData = music->FindComponent<ComponentMusic>().lock();

    double beat = musicData->GetCurrentBeat();

    // Beat duration and scale limits
    double beatCycle = 1.0;
    // Progress within the beat cycle (0.0 to 1.0)
    double beatProgress = fmod(beat, beatCycle) / beatCycle;

    // Minimum and maximum scales for interpolation
    glm::vec3 minScale(0.5f, 0.5f, 0.5f);
    glm::vec3 maxScale(0.6f, 0.6f, 0.6f);

    // Use a smooth sine wave for fluidity
    float sineWave = 0.5f * (1.0f - cos(beatProgress * glm::two_pi<float>()));

    // Interpolate scale based on the sine wave
    glm::vec3 interpolatedScale = glm::mix(minScale, maxScale, sineWave);

    // Apply the new scale to the game object
    gameObject->GetSprite()->setScale(interpolatedScale);
}
