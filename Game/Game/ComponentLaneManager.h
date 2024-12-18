#pragma once

#include "Engine/Component.h"

using namespace std;


class ComponentLaneManager : public MyEngine::Component
{
public:
	void Init(rapidjson::Value& serializedData) override;
	void Update(float) override;
	void CreateLane(string key, glm::vec3);
	void CreateGrid();
	void ParseNoteSheet();

private:
	glm::vec3 _offset;
	std::vector<string> _keys;
	std::vector<pair<float, float>> _sheet;
	std::vector<MyEngine::GameObject*> _lanes;
	int amountOfLanes;
	float noteSheet[][];
};
