#include "ComponentNutNote.h"
#include "ComponentMusic.h"
#include "Engine/MyEngine.h"
#include "Engine/Component.h"
#include "iostream"
#include <glm/ext/scalar_common.hpp>
//#include "ComponentLaneManager.h"

ComponentNutNote::ComponentNutNote() {
    // Capture the time/beat when the nut is created
    music = MyEngine::Engine::GetInstance()->GetGameObject("root").lock();
    musicData = music->FindComponent<ComponentMusic>().lock();
    startBeat = musicData->GetCurrentBeat();  // Record the current beat as the start beat
    auto gameObject = GetGameObject().lock();
}

void ComponentNutNote::PrepareNut(float start, float end, float intialBeat, float destination)
{
    std::cout << "Prepared!" << "\n";
    startPos = start;
    endPos = end;
    startBeat = intialBeat;
    DestinationBeat = destination;
}

float ComponentNutNote::GetDestinationBeat()
{
    return DestinationBeat;
}

void ComponentNutNote::Update(float delta) {
    // 1. Retrieve the current beat from the Music Component
    double currentBeat = musicData->GetCurrentBeat();
    auto gameObject = GetGameObject().lock();
    auto pos = gameObject->GetPosition();
    // 2. Calculate LERP factor 't'
    float t = (currentBeat - startBeat) / (DestinationBeat - startBeat);
    t = glm::clamp(t, 0.0f, 1.2f);  // Ensure 't' stays within [0, 1]

    // 3. Interpolate the X position using LERP
    float newPosX = (1 - t) * startPos + t * endPos;
    gameObject->SetPosition(glm::vec3(newPosX, pos.y, pos.z));
}