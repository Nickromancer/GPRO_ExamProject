#pragma once

#include "Engine/Component.h"
#include "sre/SpriteAtlas.hpp"
#include "sre/Sprite.hpp"

class ComponentRendererSprite : public MyEngine::Component {
public:
	virtual void Init(rapidjson::Value& serializedData) override;
	virtual void Render(sre::RenderPass& renderPass) override;

	void SetSprite(std::string idAtlas, std::string idSprite);
	sre::Sprite* GetSprite() { return &_sprite; }

protected:
	sre::Sprite _sprite;

private:
	std::shared_ptr<sre::SpriteAtlas> _atlas;
};