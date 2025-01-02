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
}

void ComponentLaneManager::KeyEvent(SDL_Event& event)
{
	float tmp_score = 0;
	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) {
		if (_player->isQPressed && _amountOfLanes >= 1)
			tmp_score += _lanes[0]->CheckNuts();
		if (_player->isWPressed && _amountOfLanes >= 2)
			tmp_score += _lanes[1]->CheckNuts();
		if (_player->isEPressed && _amountOfLanes >= 3)
			tmp_score += _lanes[2]->CheckNuts();
		if (_player->isRPressed && _amountOfLanes >= 4)
			tmp_score += _lanes[3]->CheckNuts();
	}
	score += tmp_score;
}

void ComponentLaneManager::Render(sre::RenderPass& renderPass)
{
	bool open = true;
	ImGui::SetNextWindowPos(ImVec2(500, 20));
	ImGui::SetNextWindowSize(ImVec2(100, 60));
	ImGui::Begin("#TestLabel", &open, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoInputs);
	ImGui::Text("Score: %d", (int) score);
	ImGui::End();
}


shared_ptr<MyEngine::GameObject> ComponentLaneManager::CreateLane(string key, glm::vec3 pos)
{
	auto engine = MyEngine::Engine::GetInstance();
	auto gameObject = GetGameObject();

	// Lane Setup
	auto lane = engine->CreateGameObject("Key_" + key, gameObject).lock();
	auto renderer = lane->CreateComponent<ComponentRendererSprite>().lock();
	lane->CreateComponent<ComponentLane>();
	renderer->SetSprite("sprites", "Box.png");
	lane->SetPosition(pos);

	// Beat Frame Setup
	auto circle = engine->CreateGameObject(key, lane).lock();
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

	for (int i = 0; i < noteArray.Size(); i++)
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
