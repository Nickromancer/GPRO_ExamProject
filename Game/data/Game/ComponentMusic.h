#pragma once

#include <chrono>
#include <condition_variable>
#include <queue>
#include <SDL_mixer.h>

#include "Engine/Component.h"

class ComponentMusic : public MyEngine::Component {
public:
	void Init(rapidjson::Value& serializedData) override;
	void Update(float) override;
	void my_audio_callback(void* userdata, Uint8* stream, int len);
	void StartProcessingThread();
	void ProcessAudio(const std::vector<Uint8>& buffer);
	double GetCurrentBeat();
	~ComponentMusic();

private:
	std::chrono::steady_clock::time_point startTime;
	std::string musicPath;
	Mix_Music* music;
	double currentBeat = 0;

	double bpm;      // Beats per minute (set manually or dynamically)
	double timeSig = 4;    // Time signature (e.g., 4.0 for 4/4 time)

	Uint8* audio_pos; // global pointer to the audio buffer to be played
	Uint32 audio_len; // remaining length of the sample we have to play
	Uint32 audio_len_init;

	Uint32 wav_length; // length of our sample
	Uint8* wav_buffer; // buffer containing our audio file
	SDL_AudioSpec wav_spec; // the specs of our piece of music

	// Shared buffer and synchronization primitives
	std::queue<std::vector<Uint8>> audioQueue;
	std::mutex audioMutex;
	std::condition_variable audioCond;
};