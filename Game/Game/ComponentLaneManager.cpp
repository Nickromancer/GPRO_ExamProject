#include "ComponentLaneManager.h"

#include "Engine/MyEngine.h"
#include "Engine/Components/ComponentRendererSprite.h"

using namespace std;

void ComponentLaneManager::Init(rapidjson::Value& serializedData)
{
	_lanes = serializedData["amountOfLanes"].GetFloat();
	auto keys = serializedData["keybinds"].GetArray();

	for (int i = 0; i < serializedData["offset"].Size(); ++i)
	{
		_offset[i] = serializedData["offset"][i].GetFloat();
	}

	for (auto& key : keys)
	{
		cout << key.GetString() << "\n";
		_keys.emplace_back(((key.GetString())));
	}

	glm::vec3 startPos = GetGameObject().lock()->GetPosition();

	for (int i = 0; i < _lanes; i++)
	{
		CreateLane(_keys[i], startPos);
		startPos += _offset;
	}

}

void ComponentLaneManager::Update(float)
{
	if (key)

}

void ComponentLaneManager::CreateLane(string key, glm::vec3 pos)
{
	auto engine = MyEngine::Engine::GetInstance();
	auto gameObject = GetGameObject();

	auto lane = engine->CreateGameObject(key, gameObject).lock();
	auto renderer = lane->CreateComponent<ComponentRendererSprite>().lock();
	renderer->SetSprite("sprites", "pngkey.com-mario-pixel-png-1691566.png");

	auto sprite = renderer->GetSprite();
	sprite->setScale({ 2, 1});

	pos.y += sprite->getSpriteSize().y;
	lane->SetPosition(pos);

}

