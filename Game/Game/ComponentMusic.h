#pragma once

#include <chrono>
#include <SDL_mixer.h>

#include "Engine/Component.h"

class ComponentMusic : public MyEngine::Component {
public:
	void Init(rapidjson::Value& serializedData) override;
	void Update(float) override;
	double TotalSamplesPlayed(double sampleRate = 44100.0);
	double CurrentSongTime(double sampleRate = 44100.0);
	double CurrentBeat();
	double CurrentBar();

	double bpm = 120;      // Beats per minute (set manually or dynamically)
	double timeSig = 4;    // Time signature (e.g., 4.0 for 4/4 time)
private:
	std::chrono::steady_clock::time_point startTime;
	std::string musicPath;
	Mix_Music* music;
};