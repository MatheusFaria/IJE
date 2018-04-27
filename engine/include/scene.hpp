#ifndef __ENGINE_SCENE__
#define __ENGINE_SCENE__

#include <string>
#include <unordered_map>

#include "gameobject.hpp"
#include "assets_manager.hpp"

namespace engine {

class Scene {
public:
    enum class State {
        created,
        loaded,
        playing,
        invalid
    };

    Scene() : Scene("", State::invalid) {}
    Scene(std::string name, State _state=State::created)
        : m_name(name), m_state(_state) {}

    virtual ~Scene() {}

    bool add_game_object(GameObject & obj);
    GameObject & get_game_object(const std::string & id);
    bool remove_game_object(const std::string & id);

    virtual bool init();
    virtual void setup();
    virtual bool shutdown();

    virtual void update();
    virtual void draw();

    inline std::string name() const { return m_name; }
    inline AssetsManager & assets_manager() { return m_assets_manager; }

protected:
    std::string                                 m_name;
    std::unordered_map<std::string, GameObject *> m_objects;

    AssetsManager m_assets_manager;

    State m_state;
};

}

#endif
