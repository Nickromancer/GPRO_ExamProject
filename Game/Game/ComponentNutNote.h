#pragma once
#include "Engine/Component.h"

class ComponentNutNote : public MyEngine::Component {
public:
	void Update(float) override;
	ComponentNutNote(float startPos, float endPos, float DestinationBeat);
	// Default constructor
	ComponentNutNote();

private:
	float startPos = -200;
	float endPos = 500;
	float DestinationBeat = 8;
	float startBeat = 9;
};