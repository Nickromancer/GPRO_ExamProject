#pragma once

#include <queue>

#include "ComponentMusic.h"
#include "ComponentNutNote.h"
#include "Engine/Component.h"

constexpr float BEAT_DELAY = 4.f;

class ComponentLane : public MyEngine::Component {
public:
	ComponentLane();
	void Update(float) override;
	void SpawnNutNote(float beat);
	void CheckNuts();
private:
	std::queue<std::shared_ptr<ComponentNutNote>> _nuts;
	std::shared_ptr<ComponentMusic> _musicManagaer;
};