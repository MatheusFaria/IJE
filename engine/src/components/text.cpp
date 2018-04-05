#include "components/text.hpp"

#include "game.hpp"
#include "log.h"
#include "sdl_log.h"

using namespace engine;

TTF_Font * load_font(std::string path, int size)
{
    INFO("Loading new font...");

    auto m_font = TTF_OpenFont(path.c_str(), size);

    if(m_font == NULL)
    {
        SDL_TTF_ERROR("Could not load font from path " << path);
        return NULL;
    }

    return m_font;
}


bool TextComponent::init()
{
    INFO("Init TextComponent");

    if (m_font_path == "")
    {
        WARN("Invalid path for font!");
        return false;
    }

    m_font = load_font(m_font_path, m_font_size);

    if(m_font == NULL) return false;

    SDL_Color color = {m_color.r, m_color.g, m_color.b, m_color.a};
    SDL_Color bg_color = {m_background_color.r, m_background_color.g,
                          m_background_color.b, m_background_color.a};

    SDL_Surface * surface = NULL;

    if (m_high_quality && bg_color.a == 0x00)
    {
        surface = TTF_RenderText_Blended(
            m_font, m_text.c_str(), color
        );
    }
    else if (m_high_quality)
    {
        surface = TTF_RenderText_Shaded(
            m_font, m_text.c_str(), color, bg_color
        );
    }
    else
    {
        surface = TTF_RenderText_Solid(
            m_font, m_text.c_str(), color
        );
    }

    if(surface == NULL)
    {
        SDL_TTF_ERROR("Could not render text " << m_text << " with font "
                      << m_font_path);
        return false;
    }

    m_texture = SDL_CreateTextureFromSurface(Game::instance.canvas(), surface);

    if (m_texture == NULL)
    {
        SDL_ERROR("Could not create texture from rendered text surface!");
        return false;
    }

    m_w = surface->w;
    m_h = surface->h;

    SDL_FreeSurface(surface);

    return true;
}

bool TextComponent::shutdown()
{
    INFO("Shutdown TextComponent");

    SDL_DestroyTexture(m_texture);
    m_texture = NULL;

    m_font = NULL;

    return true;
}

void TextComponent::draw()
{
    auto position = m_game_object->get_position();

    SDL_Rect renderQuad = {
        static_cast<int>(position.first),
        static_cast<int>(position.second),
        m_w,
        m_h
    };

    SDL_RenderCopy(Game::instance.canvas(), m_texture, NULL, &renderQuad);
}

