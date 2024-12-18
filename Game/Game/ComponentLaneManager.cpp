#include "ComponentLaneManager.h"

#include "Engine/MyEngine.h"
#include "Engine/Components/ComponentRendererSprite.h"
#include "ComponentLane.h"

using namespace std;
using namespace rapidjson;

void ComponentLaneManager::Init(rapidjson::Value& serializedData)
{
	_amountOfLanes = serializedData["amountOfLanes"].GetFloat();
	auto keys = serializedData["keybinds"].GetArray();
	_noteSheet = serializedData["noteSheet"].GetArray();


	for (int i = 0; i < serializedData["offset"].Size(); ++i)
	{
		_offset[i] = serializedData["offset"][i].GetFloat();
	}

	for (auto& key : keys)
	{
		_keys.emplace_back(((key.GetString())));
	}

	ParseNoteSheet();
	CreateGrid();

}

void ComponentLaneManager::Update(float)
{

}

void ComponentLaneManager::CreateLane(string key, glm::vec3 pos)
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
}

void ComponentLaneManager::CreateGrid()
{
	glm::vec3 startPos = GetGameObject().lock()->GetPosition();

	for (int i = 0; i < _amountOfLanes; i++)
	{
		CreateLane(_keys[i], startPos);
		startPos += _offset;
	}
}

void ComponentLaneManager::ParseNoteSheet()
{
	for (int i = 0; i < _noteSheet.Size(); ++i)
	{
		_sheet.emplace_back(_noteSheet[i][0].GetFloat(), _noteSheet[i][1].GetFloat());
	}
}
