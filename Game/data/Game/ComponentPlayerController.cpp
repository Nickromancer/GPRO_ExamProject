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
            case SDLK_q:
                isQPressed = true;
                break;
            case SDLK_w:
                isWPressed = true;
                break;
            case SDLK_e:
                isEPressed = true;
                break;
            case SDLK_r:
                isRPressed = true;
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
            case SDLK_q:
                isQPressed = false;
                break;
            case SDLK_w:
                isWPressed = false;
                break;
            case SDLK_e:
                isEPressed = false;
                break;
            case SDLK_r:
                isRPressed = false;
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