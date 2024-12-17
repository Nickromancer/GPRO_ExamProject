#pragma once

#include "Engine/Component.h"

using namespace std;
class ComponentLaneManager : public MyEngine::Component {
private:
	int _lanes;
	glm::vec3 _offset;
	std::vector<std::string> _keys;
public:
	void Init(rapidjson::Value& serializedData) override;
	void Update(float) override;
	void CreateLane(string key, glm::vec3);
};
