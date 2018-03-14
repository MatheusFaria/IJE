#ifndef __ENGINE_GAME_OBJECT__
#define __ENGINE_GAME_OBJECT__

#include <string>
#include <list>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>

namespace engine {

class Component;

class GameObject {
public:
    enum class State {
        enabled,
        disabled,
        invalid
    };

    GameObject() : GameObject("", State::invalid) {}
    GameObject(std::string name, State state=State::enabled)
        : x(0), y(0), w(0), h(0), rotation(0), m_name(name),
          m_state(state) {}

    virtual ~GameObject() {}

    virtual bool init();
    virtual void setup();
    virtual bool shutdown();

    virtual void update();
    virtual void draw();

    bool add_component(Component & component);

    template<typename T>
    T * get_component()
    {
        return dynamic_cast<T *>(m_components[std::type_index(typeid(T))].front());
    }

    template<typename T>
    std::list<Component *> get_components();

    inline std::string name()  const { return m_name; }
    inline State       state() const { return m_state; }

    inline void set_position(double _x, double _y) { x = _x; y = _y; }
    inline void set_size(double _w, double _h) { w = _w; h = _h; }

    double x, y;
    double w, h;
    double rotation;

protected:
    std::string m_name;
    State       m_state;
    std::unordered_map<std::type_index, std::list<Component *> > m_components;
};

}

#endif
