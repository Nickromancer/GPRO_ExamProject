#pragma once
#include "Engine/Component.h"

class ComponentNutNote : public MyEngine::Component {
public:
	void Update(float) override;
	ComponentNutNote();
	void PrepareNut(float start, float end, float arrive, float destination);
	float GetDestinationBeat();
private:
	float startPos;
	float endPos;
	float DestinationBeat;
	float startBeat = 9;
};