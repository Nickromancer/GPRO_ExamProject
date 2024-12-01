#include "ComponentNode.h"

#include "ComponentMusic.h"
#include "Engine/MyEngine.h"

void ComponentNode::Init(rapidjson::Value& serializedData)
{
	startTime = std::chrono::steady_clock::now();
}

void ComponentNode::Update(float delta)
{

	auto gameObject = GetGameObject().lock();
	auto music = MyEngine::Engine::GetInstance()->GetGameObject("root").lock();

	auto musicData = music->FindComponent<ComponentMusic>().lock();

	double beat = musicData->GetCurrentBeat();

	//std::chrono::steady_clock::time_point elapsed = std::chrono::steady_clock::now();
	//
	//if (std::chrono::duration_cast<std::chrono::seconds>(elapsed - startTime).count() % 2 < 1)
	//	gameObject->SetScale(glm::vec3(gameObject->GetScale().x + delta, gameObject->GetScale().y + delta, gameObject->GetScale().z));
	//else
	//	gameObject->SetScale(glm::vec3(gameObject->GetScale().x - delta, gameObject->GetScale().y - delta, gameObject->GetScale().z));

	if (static_cast<int>(beat) % 2 < 1)
		gameObject->SetScale(glm::vec3(gameObject->GetScale().x + delta, gameObject->GetScale().y + delta, gameObject->GetScale().z));
	else
		gameObject->SetScale(glm::vec3(gameObject->GetScale().x - delta, gameObject->GetScale().y - delta, gameObject->GetScale().z));

}
