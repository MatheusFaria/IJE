#include "components/image.hpp"

#include "game.hpp"
#include "log.h"
#include "sdl_log.h"

using namespace engine;

struct Image {
    SDL_Texture * texture;
    unsigned int w;
    unsigned int h;
};

Image * load_image(std::string path)
{
    INFO("Loading new image...");

    SDL_Surface * image = IMG_Load(path.c_str());

    if (image == NULL)
    {
        SDL_IMG_ERROR("Could not load image from path " << path);
        return NULL;
    }

    auto m_texture = SDL_CreateTextureFromSurface(Game::instance.canvas(),
                                                  image);

    if (m_texture == NULL)
    {
        SDL_ERROR("Could not create texture from image!");
        return NULL;
    }

    Image * img = new Image;
    img->texture = m_texture;
    img->w = image->w;
    img->h = image->h;

    SDL_FreeSurface(image);

    return img;
}

bool ImageComponent::init()
{
    INFO("Init ImageComponent");

    if (m_path == "")
    {
        WARN("Invalid path for image!");
        return false;
    }

    auto image = load_image(m_path);

    m_texture = image->texture;
    m_w = image->w;
    m_h = image->h;

    m_game_object->set_size(m_w, m_h);
    update_canvas_rect();

    m_image_rect.x = 0;
    m_image_rect.y = 0;
    m_image_rect.w = m_w;
    m_image_rect.h = m_h;

    return true;
}

bool ImageComponent::shutdown()
{
    INFO("Shutdown ImageComponent");

    m_texture = NULL;

    return true;
}

void ImageComponent::draw()
{
    update_canvas_rect();

    SDL_RenderCopy(Game::instance.canvas(), m_texture,
                   &m_image_rect, &m_canvas_rect);
}



void ImageComponent::update_canvas_rect()
{
    auto position = m_game_object->get_position();

    m_canvas_rect.x = position.first;
    m_canvas_rect.y = position.second;
    m_canvas_rect.w = m_game_object->w;
    m_canvas_rect.h = m_game_object->h;
}
