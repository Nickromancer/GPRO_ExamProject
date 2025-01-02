#pragma once

#include "SDL.h"
#include "Engine/Component.h"

class ComponentPlayerController: public MyEngine::Component {

public:
	void Init(rapidjson::Value& serializedData) override;
	void Update(float delta) override;
	void KeyEvent(SDL_Event&) override;

	bool isQPressed = false;
	bool isWPressed = false;
	bool isEPressed = false;
	bool isRPressed = false;
	bool isEnterPressed = false;

public:
	ComponentPlayerController() = default;
};
