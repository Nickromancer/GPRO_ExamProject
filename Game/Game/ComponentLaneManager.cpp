#include "ComponentLaneManager.h"

#include "Engine/MyEngine.h"
#include "Engine/Components/ComponentRendererSprite.h"
#include "ComponentLane.h"

using namespace std;
using namespace rapidjson;

void ComponentLaneManager::Init(rapidjson::Value& serializedData)
{
	_amountOfLanes = serializedData["amountOfLanes"].GetInt();

	ParseOffsetVector(serializedData["offset"]);
	ParseKeybinds(serializedData["keybinds"]);
	ParseNoteSheet(serializedData["noteSheet"]);
	CreateGrid();

}

void ComponentLaneManager::Update(float)
{

}

shared_ptr<MyEngine::GameObject> ComponentLaneManager::CreateLane(string key, glm::vec3 pos)
{
	auto engine = MyEngine::Engine::GetInstance();
	auto gameObject = GetGameObject();

	auto lane = engine->CreateGameObject(key, gameObject).lock();
	auto renderer = lane->CreateComponent<ComponentRendererSprite>().lock();
	lane->CreateComponent<ComponentLane>();
	renderer->SetSprite("sprites", "pngkey.com-mario-pixel-png-1691566.png");

	auto sprite = renderer->GetSprite();
	sprite->setScale({ 2, 1});

	pos.y += sprite->getSpriteSize().y;
	lane->SetPosition(pos);

	return lane;
}

void ComponentLaneManager::CreateGrid()
{
	glm::vec3 startPos = GetGameObject().lock()->GetPosition();

	for (unsigned int i = 0; i < _amountOfLanes; i++)
	{
		auto lane = CreateLane(_keys[i], startPos);
		_lanes.push_back(lane);
		startPos += _offset;
	}
}

void ComponentLaneManager::ParseNoteSheet(rapidjson::Value& noteSheet)
{
	auto noteArray = noteSheet.GetArray();

	for (int i = 0; i < noteArray.Size(); ++i)
	{
		_sheet.emplace_back(noteArray[i][0].GetFloat(), noteArray[i][1].GetFloat());
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
