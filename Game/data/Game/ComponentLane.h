#pragma once

#include <queue>

#include "ComponentMusic.h"
#include "ComponentNutNote.h"
#include "Engine/Component.h"

constexpr float BEAT_DELAY = 8.f;
constexpr float BEAT_FRAME = 1.f;
constexpr float BEAT_AFTER_TIME = 1.f;
constexpr float GOOD_SCORE = 10.f;
constexpr float BAD_SCORE = -10.f;


class ComponentLane : public MyEngine::Component {
public:
	ComponentLane();
	void Update(float) override;
	void SpawnNutNote(float beat);
	float CheckNuts();
	void Score();
private:
	std::queue<std::shared_ptr<ComponentNutNote>> _nuts;
	std::shared_ptr<ComponentMusic> _musicManagaer;
	Mix_Chunk* soundGood;
	Mix_Chunk* soundBad;

};