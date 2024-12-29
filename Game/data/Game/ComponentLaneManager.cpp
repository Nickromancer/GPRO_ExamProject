#include "ComponentLaneManager.h"

#include "Engine/MyEngine.h"
#include "Engine/Components/ComponentRendererSprite.h"
#include "ComponentLane.h"
#include "ComponentMusic.h"

using namespace std;
using namespace rapidjson;

void ComponentLaneManager::Init(rapidjson::Value& serializedData)
{
	auto root = MyEngine::Engine::GetInstance()->GetGameObject("root").lock();

	_musicManagaer = root->FindComponent<ComponentMusic>().lock();
	_player = root->FindComponent<ComponentPlayerController>().lock();
	_amountOfLanes = serializedData["amountOfLanes"].GetInt();

	ParseOffsetVector(serializedData["offset"]);
	ParseKeybinds(serializedData["keybinds"]);
	ParseNoteSheet(serializedData["noteSheet"]);
	CreateGrid();

}

void ComponentLaneManager::Update(float)
{
	if (!_sheet.empty())
	{
		if (_musicManagaer->GetCurrentBeat() >= _sheet[0].first - BEAT_DELAY)
		{
			_lanes[_sheet[0].second]->SpawnNutNote(_sheet[0].first - BEAT_DELAY);
			_sheet.erase(_sheet.begin());
		}
	}

	if (_player->isSpacePressed)
	{
		if (_player->isQPressed && _amountOfLanes >= 1)
			_lanes[0]->CheckNuts();
		if (_player->isWPressed && _amountOfLanes >= 2)
			_lanes[1]->CheckNuts();
		if (_player->isEPressed && _amountOfLanes >= 3)
			_lanes[2]->CheckNuts();
		if (_player->isRPressed && _amountOfLanes >= 4)
			_lanes[3]->CheckNuts();
	}

}

shared_ptr<MyEngine::GameObject> ComponentLaneManager::CreateLane(string key, glm::vec3 pos)
{
	auto engine = MyEngine::Engine::GetInstance();
	auto gameObject = GetGameObject();

	auto lane = engine->CreateGameObject("Key_" + key, gameObject).lock();
	auto circle = engine->CreateGameObject(key, lane).lock();

	// Lane Setup
	auto renderer = lane->CreateComponent<ComponentRendererSprite>().lock();
	lane->CreateComponent<ComponentLane>();
	renderer->SetSprite("sprites", "Box.png");
	lane->SetPosition(pos);

	// Beat Frame Setup
	auto rendererCircle = circle->CreateComponent<ComponentRendererSprite>().lock();
	rendererCircle->SetSprite("sprites", key + ".png");
	rendererCircle->GetSprite()->setScale(glm::vec2(0.5f));
	auto width = renderer->GetSprite()->getSpriteSize().x;
	renderer->GetSprite()->setScale(glm::vec2(0));
	rendererCircle->GetSprite()->setPosition(glm::vec2(gameObject.lock()->GetPosition().x + width / 2, pos.y));

	return lane;
}

void ComponentLaneManager::CreateGrid()
{
	glm::vec3 startPos = GetGameObject().lock()->GetPosition();
	for (unsigned int i = 0; i < _amountOfLanes; i++)
	{
		auto lane = CreateLane(_keys[i], startPos);
		_lanes.push_back(lane->FindComponent<ComponentLane>().lock());
		startPos += _offset;
	}
}

void ComponentLaneManager::ParseNoteSheet(rapidjson::Value& noteSheet)
{
	auto noteArray = noteSheet.GetArray();
	//TODO change back!
	for (int i = 0; i < 100; i = i + 2)
	{
		_sheet.emplace_back(i, noteArray[0][1].GetFloat());
		_sheet.emplace_back(i + 0.01f, noteArray[1][1].GetFloat());
		_sheet.emplace_back(i + 0.02f, noteArray[2][1].GetFloat());
		_sheet.emplace_back(i + 0.03f, noteArray[3][1].GetFloat());
	}
}

void ComponentLaneManager::ParseKeybinds(rapidjson::Value& keybinds)
{
	auto keys = keybinds.GetArray();

	for (int i = 0; i < keys.Size(); ++i)
	{
		_keys.emplace_back(keys[i].GetString());
	}
}

void ComponentLaneManager::ParseOffsetVector(rapidjson::Value& offset)
{
	for (unsigned int i = 0; i < offset.Size(); ++i)
	{
		_offset[i] = offset[i].GetFloat();
	}
}
