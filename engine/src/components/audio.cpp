#include "components/audio.hpp"

#include "game.hpp"
#include "log.h"
#include "sdl_log.h"

using namespace engine;

Mix_Music * load_music(std::string path)
{
    Mix_Music * music = Mix_LoadMUS(path.c_str());
    if (music == NULL)
    {
        SDL_MIX_ERROR("Could not load music from path " << path);
        return NULL;
    }

    return music;
}

Mix_Chunk * load_sound(std::string path)
{
    Mix_Chunk * sound = Mix_LoadWAV(path.c_str());
    if (sound == NULL)
    {
        SDL_MIX_ERROR("Could not load sound from path " << path);
        return NULL;
    }

    return sound;
}

bool AudioComponent::init()
{
    INFO("Init audio component");

    if (m_is_music)
    {
        m_music = load_music(m_path);
        if (m_music == NULL) return false;
    }
    else
    {
        m_sound = load_sound(m_path);
        if (m_sound == NULL) return false;
    }

    return true;
}

bool AudioComponent::shutdown()
{
    INFO("Shutdown audio component");
    return true;
}

void AudioComponent::update()
{
    if(m_play_on_start)
    {
        play();
        m_play_on_start = false;
    }
}

void AudioComponent::play(int loops, int channel)
{
    if(m_is_music)
    {
        if(m_audio_state == AudioState::stopped) Mix_PlayMusic(m_music, loops);
        else if (m_audio_state == AudioState::paused) Mix_ResumeMusic();
    }
    else
    {
        if(m_audio_state == AudioState::stopped)
            Mix_PlayChannel(channel, m_sound, loops);
        else if (m_audio_state == AudioState::paused)
            Mix_Resume(channel);
    }

    m_audio_state = AudioState::playing;
}

void AudioComponent::stop(int channel)
{
    if(m_is_music) Mix_HaltMusic();
    else Mix_HaltChannel(channel);

    m_audio_state = AudioState::stopped;
}

void AudioComponent::pause(int channel)
{
    if(m_is_music) Mix_PauseMusic();
    else Mix_Pause(channel);

    m_audio_state = AudioState::paused;
}
