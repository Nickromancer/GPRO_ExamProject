#include "ComponentMusic.h"

#include <chrono>
#include <SDL_timer.h>

#include "Engine/MyEngine.h"
#include <SDL.h>

using namespace std;

void ComponentMusic::Init(rapidjson::Value& serilizedData) {
    musicPath = serilizedData["path"].GetString();

    // Initialize SDL.
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        return;
    }

    // local variables
    static Uint32 wav_length; // length of our sample
    static Uint8* wav_buffer; // buffer containing our audio file
    static SDL_AudioSpec wav_spec; // the specs of our piece of music

    /* Load the WAV */
    // the specs, length and buffer of our wav are filled
    if (SDL_LoadWAV(musicPath.c_str(), &wav_spec, &wav_buffer, &wav_length) == nullptr) {
        return;
    }

    // set the callback function
    wav_spec.callback = [](void* userdata, Uint8* stream, int len) {
        static_cast<ComponentMusic*>(userdata)->my_audio_callback(userdata, stream, len);
    };
    wav_spec.userdata = this;

    // set our global static variables
    audio_pos = wav_buffer; // copy sound buffer
    audio_len = wav_length; // copy file length
    audio_len_init = audio_len; // copy file length

    cout << audio_len << "\n";

    /* Open the audio device */
    if (SDL_OpenAudio(&wav_spec, nullptr) < 0) {
        cout << "Couldn't open audio: " << SDL_GetError() << "\n";
        return;
    }

    /* Start playing */
    SDL_PauseAudio(0);

    // wait until we're don't playing
    while (audio_len > 0) {
        SDL_Delay(100);
    }

    // shut everything down
    SDL_CloseAudio();
    SDL_FreeWAV(wav_buffer);
}


void ComponentMusic::Update(float delta)
{
    double totalSamples = TotalSamplesPlayed();
    double currentSongTime = CurrentSongTime();
    double currentBeat = CurrentBeat();
    double currentBar = CurrentBar();

    //std::cout << "Samples Played: " << totalSamples << "\n";
    //std::cout << "Song Time (seconds): " << currentSongTime << "\n";
    //std::cout << "Current Beat: " << currentBeat << "\n";
    //std::cout << "Current Bar: " << currentBar << "\n";

    std::cout << "Audio Length " << audio_len << "\n";
    std::cout << "Audio Position " << audio_pos << "\n";



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

void ComponentMusic::my_audio_callback(void* userdata, Uint8* stream, int len)
{
    if (audio_len == 0)
        return;

    len = (len > audio_len ? audio_len : len);
    SDL_memcpy (stream, audio_pos, len); 					// simply copy from one buffer into the other
    //SDL_MixAudio(stream, audio_pos, len, SDL_MIX_MAXVOLUME);// mix from one buffer into another

    audio_pos += len;
    audio_len -= len;

    //cout << audio_len_init - audio_len << "\n";

    double cst = ((audio_len_init - audio_len) / 4) / 44052.8;
    double bpm = 120;

    double beat = ((cst / 60) * bpm);

    cout << beat << "\n";

    return;
}
