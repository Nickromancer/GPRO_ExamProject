#include "sre/SpriteAtlas.hpp"

#include "Engine/MyEngine.h"
#include "Engine/ComponentFactory.h"

#include "Game/ComponentMusic.h"
#include "Game/ComponentNode.h"

//#include "Game/ComponentCamera.h"
//#include "Game/ComponentRendererMesh.h"
//#include "Game/ComponentController.h"
//#include "Game/ComponentLayout.h"

MyEngine::Engine engine;

int main() {
	//MyEngine::ComponentFactory::RegisterComponentOfType("CONTROLLER",		[]() { return std::make_shared<ComponentController>();		});
	//MyEngine::ComponentFactory::RegisterComponentOfType("CAMERA",			[]() { return std::make_shared<ComponentCamera>();			});
	//MyEngine::ComponentFactory::RegisterComponentOfType("CUBE_RENDERER",	[]() { return std::make_shared<ComponentRendererMesh>();	});
	//MyEngine::ComponentFactory::RegisterComponentOfType("LAYOUT", []() { return std::make_shared<ComponentLayout>();	});
	MyEngine::ComponentFactory::RegisterComponentOfType("MUSIC", []() {return std::make_shared<ComponentMusic>();  });
	//MyEngine::ComponentFactory::RegisterComponentOfType("NODE", []() {return std::make_shared<ComponentNode>();  });



	engine.Init("data/scene.json");
}
