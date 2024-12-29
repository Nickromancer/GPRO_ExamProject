#include "ComponentMusic.h"
#include <chrono>
#include <mutex>
#include <SDL_timer.h>
#include "Engine/MyEngine.h"
#include <SDL.h>


using namespace std;

void ComponentMusic::Init(rapidjson::Value& serilizedData) {
    musicPath = serilizedData["path"].GetString();
    bpm = serilizedData["BPM"].GetFloat();

    // Initialize SDL.
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        return;
    }

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


    /* Open the audio device */
    if (SDL_OpenAudio(&wav_spec, nullptr) < 0) {
        cout << "Couldn't open audio: " << SDL_GetError() << "\n";
        return;
    }

    startTime = std::chrono::steady_clock::now();

    /* Start playing */
    SDL_PauseAudio(0);

    StartProcessingThread();
}

void ComponentMusic::Update(float delta)
{
}

void ComponentMusic::my_audio_callback(void* userdata, Uint8* stream, int len)
{
    if (audio_len == 0)
        return;

    len = (len > audio_len ? audio_len : len);

    {
        // Copy audio data into a local buffer
        std::vector<Uint8> buffer(stream, stream + len);
        // Lock and enqueue the buffer for processing
        std::lock_guard<std::mutex> lock(audioMutex);
        audioQueue.push(buffer);
    }

    // Notify the processing thread
    audioCond.notify_one();

    SDL_memcpy(stream, audio_pos, len); // Write audio to output
    audio_pos += len;
    audio_len -= len;
}

void ComponentMusic::StartProcessingThread()
{
    std::thread([this]() {
        while (audio_len > 0 || !audioQueue.empty()) {
            std::vector<Uint8> buffer;

            {
                // Wait until there is audio data in the queue
                std::unique_lock<std::mutex> lock(audioMutex);
                audioCond.wait(lock, [this] { return !audioQueue.empty() || audio_len == 0; });

                if (!audioQueue.empty()) {
                    // Retrieve the next buffer
                    buffer = std::move(audioQueue.front());
                    audioQueue.pop();
                }
            }

            if (!buffer.empty()) {
                // Process the audio data (e.g., calculate beats)
                ProcessAudio(buffer);
            }
        }
        }).detach();
}

void ComponentMusic::ProcessAudio(const std::vector<Uint8>& buffer)
{
    static size_t totalSamplesProcessed = 0;

    // Derive bytes per sample from audio format
    int bytesPerSample = SDL_AUDIO_BITSIZE(wav_spec.format) / 8;
    int channels = wav_spec.channels;
    size_t samples = buffer.size() / (bytesPerSample * channels);

    totalSamplesProcessed += samples;

    double elapsedTime = totalSamplesProcessed / static_cast<double>(wav_spec.freq);
    double beat = (elapsedTime / 60.0) * bpm;

    system("cls");
    std::cout << "Elapsed Time: " << elapsedTime << " s, Current Beat: " << beat << "\n";
    currentBeat = beat;

}

double ComponentMusic::GetCurrentBeat()
{
    return currentBeat;
}

ComponentMusic::~ComponentMusic() {
    SDL_CloseAudio();
    SDL_FreeWAV(wav_buffer);
}


