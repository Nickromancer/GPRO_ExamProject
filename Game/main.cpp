#include "Engine/MyEngine.h"
#include "Engine/ComponentFactory.h"

#include "Game/ComponentMusic.h"
#include "Game/ComponentNode.h"
#include "Game/ComponentBackground.h"
#include "Game/ComponentLaneManager.h"


MyEngine::Engine engine;

int main() {
	MyEngine::ComponentFactory::RegisterComponentOfType("MUSIC", []() {return std::make_shared<ComponentMusic>();  });
	MyEngine::ComponentFactory::RegisterComponentOfType("NODE", []() {return std::make_shared<ComponentNode>();  });
	MyEngine::ComponentFactory::RegisterComponentOfType("BACKGROUND", []() { return std::make_shared<ComponentBackground>(); });
	MyEngine::ComponentFactory::RegisterComponentOfType("LANE_MANAGER", []() { return std::make_shared<ComponentLaneManager>(); });

	engine.Init("data/scene.json");
}
