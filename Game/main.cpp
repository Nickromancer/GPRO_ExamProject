#include "Engine/MyEngine.h"
#include "Engine/ComponentFactory.h"

#include "data/Game/ComponentMusic.h"
#include "data/Game/ComponentNode.h"
#include "data/Game/ComponentBackground.h"
#include "data/Game/ComponentLaneManager.h"
#include "data/Game/ComponentNutNote.h"
#include "data/Game/ComponentPlayerController.h"

MyEngine::Engine engine;

int main() {
	MyEngine::ComponentFactory::RegisterComponentOfType("MUSIC", []() {return std::make_shared<ComponentMusic>();  });
	MyEngine::ComponentFactory::RegisterComponentOfType("NODE", []() {return std::make_shared<ComponentNode>();  });
	MyEngine::ComponentFactory::RegisterComponentOfType("BACKGROUND", []() { return std::make_shared<ComponentBackground>(); });
	MyEngine::ComponentFactory::RegisterComponentOfType("LANE_MANAGER", []() { return std::make_shared<ComponentLaneManager>(); });
	MyEngine::ComponentFactory::RegisterComponentOfType("NUTNOTE", []() { return std::make_shared<ComponentNutNote>(); });
	MyEngine::ComponentFactory::RegisterComponentOfType("PLAYER_CONTROLLER", []() { return std::make_shared<ComponentPlayerController>(); });

  engine.Init("data/scene.json");
}