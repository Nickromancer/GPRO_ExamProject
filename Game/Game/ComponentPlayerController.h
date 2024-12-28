#pragma once

#include "SDL.h"
#include "Engine/Component.h"

class ComponentPlayerController: public MyEngine::Component {

public:
	void Init(rapidjson::Value& serializedData) override;
	void Update(float delta) override;
	void KeyEvent(SDL_Event&) override;

	bool isF1Pressed = false;
	bool isF2Pressed = false;
	bool isF3Pressed = false;
	bool isF4Pressed = false;
	bool isEnterPressed = false;
	bool isSpacePressed = false;
public:

	ComponentPlayerController() = default;
};
