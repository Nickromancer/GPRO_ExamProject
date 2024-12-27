#include "sre/SpriteAtlas.hpp"

#include "Engine/MyEngine.h"
#include "Engine/ComponentFactory.h"

#include "Game/ComponentMusic.h"
#include "Game/ComponentNode.h"
#include "Game/ComponentBackground.h"
#include "Game/ComponentNutNote.h"
<<<<<<< Updated upstream
=======
#include "Game/ComponentPlayerController.h"
>>>>>>> Stashed changes


MyEngine::Engine engine;

int main() {
<<<<<<< Updated upstream
	MyEngine::ComponentFactory::RegisterComponentOfType("MUSIC", []() {return std::make_shared<ComponentMusic>();  });
	MyEngine::ComponentFactory::RegisterComponentOfType("NODE", []() {return std::make_shared<ComponentNode>();  });
	MyEngine::ComponentFactory::RegisterComponentOfType("BACKGROUND", []() { return std::make_shared<ComponentBackground>(); });
	MyEngine::ComponentFactory::RegisterComponentOfType("NUTNOTE", []() { return std::make_shared<ComponentNutNote>(); });
=======
    MyEngine::ComponentFactory::RegisterComponentOfType("MUSIC", []() {return std::make_shared<ComponentMusic>();  });
    MyEngine::ComponentFactory::RegisterComponentOfType("NODE", []() {return std::make_shared<ComponentNode>();  });
    MyEngine::ComponentFactory::RegisterComponentOfType("BACKGROUND", []() { return std::make_shared<ComponentBackground>(); });
    MyEngine::ComponentFactory::RegisterComponentOfType("NUTNOTE", []() { return std::make_shared<ComponentNutNote>(); });
    MyEngine::ComponentFactory::RegisterComponentOfType("PLAYER_CONTROLLER", []() { return std::make_shared<ComponentPlayerController>(); });
>>>>>>> Stashed changes

    engine.Init("data/scene.json");
    }