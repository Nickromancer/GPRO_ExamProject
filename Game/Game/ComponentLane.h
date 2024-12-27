#pragma once

#include "Engine/Component.h"

class ComponentLane : public MyEngine::Component {
public:
	ComponentLane();
	void Update(float) override;
	void SpawnNutNote();
};