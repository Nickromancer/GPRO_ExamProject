#pragma once

#include "ComponentLane.h"
#include "ComponentMusic.h"
#include "ComponentPlayerController.h"
#include "Engine/Component.h"

using namespace std;
using namespace rapidjson;

class ComponentLaneManager : public MyEngine::Component
{
	void Init(rapidjson::Value& serializedData) override;
	void Update(float) override;
	void KeyEvent(SDL_Event&) override;
	void Render(sre::RenderPass& renderPass) override;

	shared_ptr<MyEngine::GameObject> CreateLane(string key, glm::vec3 pos);
	void CreateGrid();
	void ParseNoteSheet(rapidjson::Value& noteSheet);
	void ParseKeybinds(rapidjson::Value& keybinds);
	void ParseOffsetVector(rapidjson::Value& offset);

private:
	glm::vec3 _offset;
	std::vector<string> _keys;
	std::vector<pair<float, float>> _sheet;
	std::vector<shared_ptr<ComponentLane>> _lanes;
	int _amountOfLanes;
	float score;
	shared_ptr<ComponentMusic> _musicManagaer;
	shared_ptr<ComponentPlayerController> _player;

};
