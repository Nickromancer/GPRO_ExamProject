#pragma once

#include <chrono>

#include "Engine/Component.h"

class ComponentNode : public MyEngine::Component {
public:
	void Init(rapidjson::Value& serializedData) override;
	void Update(float) override;

	std::chrono::steady_clock::time_point startTime;
};