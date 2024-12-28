#include "ComponentLane.h"

#include "ComponentNutNote.h"
#include "Engine/MyEngine.h"
#include "Engine/Components/ComponentRendererSprite.h"

class ComponentMusic;

ComponentLane::ComponentLane()
{
	std::cout << "lane Created!" << "\n";

	auto engine = MyEngine::Engine::GetInstance();

	auto root = MyEngine::Engine::GetInstance()->GetGameObject("root").lock();

	_musicManagaer = root->FindComponent<ComponentMusic>().lock();
}

void ComponentLane::Update(float x)
{
	if (!_nuts.empty())
	{
	    if (_nuts.front()->GetDestinationBeat() <= _musicManagaer->GetCurrentBeat())
	    {
	        auto nut = _nuts.front()->GetGameObject().lock().get();
	        MyEngine::Engine::GetInstance()->DestroyGameObject(nut);
			_nuts.pop();
	    }
	}

}

void ComponentLane::SpawnNutNote(float beat)
{
	auto engine = MyEngine::Engine::GetInstance();
	auto gameObject = GetGameObject();

	auto nutNode = engine->CreateGameObject("NUT_" + std::to_string(beat), gameObject).lock();
	auto renderer = nutNode->CreateComponent<ComponentRendererSprite>().lock();
	auto nut = nutNode->CreateComponent<ComponentNutNote>().lock();
	nut->PrepareNut(gameObject.lock()->GetPosition().x - 2085 / 2, gameObject.lock()->GetPosition().y + 2085 / 2, beat, beat + BEAT_DELAY);

	_nuts.push(nut);

	renderer->SetSprite("sprites", "coconut1_2.png");

	auto sprite = renderer->GetSprite();
	sprite->setScale({ 1, 1 });

	nutNode->SetPosition(glm::vec3(gameObject.lock()->GetPosition().x - 2085 / 2, gameObject.lock()->GetPosition().y, 0));
}

void ComponentLane::CheckNuts()
{
	if (!_nuts.empty())
	{
		if (_nuts.front()->GetDestinationBeat() - 1 <= _musicManagaer->GetCurrentBeat() && _nuts.front()->GetDestinationBeat() + 1 >= _musicManagaer->GetCurrentBeat())
		{
			auto nut = _nuts.front()->GetGameObject().lock().get();
			MyEngine::Engine::GetInstance()->DestroyGameObject(nut);
			_nuts.pop();
		}
	}
}
