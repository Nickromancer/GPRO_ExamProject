#pragma

#include "ComponentPlayerController.h"
#include "Engine/MyEngine.h"
#include "ComponentMusic.h"
#include "Engine/Component.h"
#include "SDL.h"
void ComponentPlayerController::Init(rapidjson::Value& serializedData) {
    if (!serializedData.IsObject()) {
        std::cerr << "Error: Serialized data is not an object!" << std::endl;
        return;
    }

    if (serializedData.HasMember("keyBindings")) {
        auto keyBindings = serializedData["keyBindings"].GetArray();
        std::cout << "Key bindings loaded." << std::endl;
    }
    else {
        std::cerr << "Error: 'keyBindings' not found in serialized data!" << std::endl;
    }
}
void ComponentPlayerController::Update(float delta) {}

void ComponentPlayerController::KeyEvent(SDL_Event & event) {

        // Poll all events in the queue
        // Check if a key was pressed
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
            case SDLK_F1:
                isF1Pressed = true;
                break;
            case SDLK_F2:
                isF2Pressed = true;
                break;
            case SDLK_F3:
                isF3Pressed = true;
                break;
            case SDLK_F4:
                isF4Pressed = true;
                break;
            case SDLK_SPACE:
                isSpacePressed = true;
                break;
            case SDLK_RETURN:
                isEnterPressed = true;
                break;
            }
        }
        // Check if a key was released
        else if (event.type == SDL_KEYUP) {
            switch (event.key.keysym.sym) {
            case SDLK_F1:
                isF1Pressed = false;
                break;
            case SDLK_F2:
                isF2Pressed = false;
                break;
            case SDLK_F3:
                isF3Pressed = false;
                break;
            case SDLK_F4:
                isF4Pressed = false;
                break;
            case SDLK_SPACE:
                isSpacePressed = false;
                break;
            case SDLK_RETURN:
                isEnterPressed = false;
                break;
            }
        }
    }