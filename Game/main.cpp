#include "sre/SpriteAtlas.hpp"

#include "Engine/MyEngine.h"
#include "Engine/ComponentFactory.h"

#include "Game/ComponentMusic.h"
#include "Game/ComponentNode.h"
#include "Game/ComponentBackground.h"


MyEngine::Engine engine;

int main() {
	MyEngine::ComponentFactory::RegisterComponentOfType("MUSIC", []() {return std::make_shared<ComponentMusic>();  });
	MyEngine::ComponentFactory::RegisterComponentOfType("NODE", []() {return std::make_shared<ComponentNode>();  });
	MyEngine::ComponentFactory::RegisterComponentOfType("BACKGROUND", []() { return std::make_shared<ComponentBackground>(); });

	engine.Init("data/scene.json");
}
