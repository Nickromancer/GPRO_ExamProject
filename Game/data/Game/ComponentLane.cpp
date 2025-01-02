#include "ComponentLane.h"

#include "ComponentNode.h"
#include "ComponentNutNote.h"
#include "Engine/MyEngine.h"
#include "Engine/Components/ComponentRendererSprite.h"

ComponentLane::ComponentLane()
{
	auto engine = MyEngine::Engine::GetInstance();
	auto root = MyEngine::Engine::GetInstance()->GetGameObject("root").lock();
	_musicManagaer = root->FindComponent<ComponentMusic>().lock();

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		std::cout << "Cannot initialize audio output" << std::endl;
		return;
	}

	soundGood = Mix_LoadWAV("data/good.wav");
	soundBad = Mix_LoadWAV("data/bad.wav");

	if (soundGood == nullptr || soundBad == nullptr)
	{
		std::cout << "there was a problem loading the sound effects" << std::endl;
		return;
	}
}

void ComponentLane::Update(float x)
{
	if (!_nuts.empty())
	{
	    if (_nuts.front()->GetDestinationBeat() + BEAT_AFTER_TIME <= _musicManagaer->GetCurrentBeat())
	    {
	        auto nut = _nuts.front()->GetGameObject().lock().get();
	        MyEngine::Engine::GetInstance()->DestroyGameObject(nut);
			_nuts.pop();
			Mix_PlayChannel(-1, soundBad, 0);
	    }
	}
}

void ComponentLane::SpawnNutNote(float beat)
{
	auto engine = MyEngine::Engine::GetInstance();
	auto gameObject = GetGameObject();
	auto laneSprite = gameObject.lock()->FindComponent<ComponentRendererSprite>().lock();
	float laneWidth = laneSprite->GetSprite()->getSpriteSize().x;

	auto nutNode = engine->CreateGameObject("NUT_" + std::to_string(beat), gameObject).lock();
	auto renderer = nutNode->CreateComponent<ComponentRendererSprite>().lock();
	auto nut = nutNode->CreateComponent<ComponentNutNote>().lock();
	nutNode->CreateComponent<ComponentNode>();
	nut->PrepareNut(gameObject.lock()->GetPosition().x - laneWidth / 2, gameObject.lock()->GetPosition().x + laneWidth / 2, beat, beat + BEAT_DELAY);

	_nuts.push(nut);

	renderer->SetSprite("sprites", "RickHead.png");
	nutNode->SetPosition(glm::vec3(nutNode->GetPosition().x, gameObject.lock()->GetPosition().y, 0));
}

float ComponentLane::CheckNuts()
{

	if (!_nuts.empty())
	{
		auto nutBeat = _nuts.front()->GetDestinationBeat();
		auto musicBeat = _musicManagaer->GetCurrentBeat();
		// Bad Timing Frame
		if (nutBeat - BEAT_FRAME <= musicBeat && nutBeat + BEAT_FRAME >= musicBeat)
		{
			// Good Timing Frame
			if (nutBeat - BEAT_FRAME / 2 <= musicBeat && nutBeat + BEAT_FRAME / 2 >= musicBeat)
			{
				auto nut = _nuts.front()->GetGameObject().lock().get();
				MyEngine::Engine::GetInstance()->DestroyGameObject(nut);
				_nuts.pop();
				Mix_PlayChannel(-1, soundGood, 0);
				return GOOD_SCORE;
			}
			auto nut = _nuts.front()->GetGameObject().lock().get();
			MyEngine::Engine::GetInstance()->DestroyGameObject(nut);
			_nuts.pop();

			Mix_PlayChannel(-1, soundBad, 0);
			return BAD_SCORE;
		}
		return BAD_SCORE;
	}
}


