#include "ComponentMusic.h"

#include <chrono>
#include <SDL_timer.h>

#include "Engine/MyEngine.h"
#include "SDL_mixer.h"

void ComponentMusic::Init(rapidjson::Value& serilizedData) {
    startTime = std::chrono::steady_clock::now();
	musicPath = serilizedData["path"].GetString();

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		std::cout << "Cannot initialize audio output " << Mix_GetError() << '\n';
		return;
	}

    music = Mix_LoadMUS(musicPath.c_str());
    if (music == nullptr)
    {
        std::cout << "Cannot load music: " << Mix_GetError() << '\n';
        return;
    }

    if (Mix_PlayMusic(music, 0) == -1)
    {
        std::cout << "Cannot play music: " << Mix_GetError() << '\n';
    }
}


void ComponentMusic::Update(float delta)
{
    double totalSamples = TotalSamplesPlayed();
    double currentSongTime = CurrentSongTime();
    double currentBeat = CurrentBeat();
    double currentBar = CurrentBar();

    //std::cout << "Samples Played: " << totalSamples << "\n";
    //std::cout << "Song Time (seconds): " << currentSongTime << "\n";
    std::cout << "Current Beat: " << currentBeat << "\n";
    //std::cout << "Current Bar: " << currentBar << "\n";

    std::cout << Mix_MusicDuration(music) << "\n";


}

double ComponentMusic::TotalSamplesPlayed(double sampleRate)
{
    if (Mix_PlayingMusic() == 0) return 0.0;

    auto currentTime = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed = currentTime - startTime;
    return elapsed.count() * sampleRate;
}

double ComponentMusic::CurrentSongTime(double sampleRate)
{
    return TotalSamplesPlayed(sampleRate) / sampleRate;
}

double ComponentMusic::CurrentBeat()
{
    double cst = CurrentSongTime();
    return (cst / 60.0) * bpm;
}

double ComponentMusic::CurrentBar()
{
    return CurrentBeat() / timeSig;
}
