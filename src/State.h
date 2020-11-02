#ifndef STATE_H
#define STATE_H

#include "StateIdentifiers.h"
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"

#include <SFML/Graphics.hpp>

#include <memory>

class StateStack;

class State
{
public:
    typedef std::unique_ptr<State> Ptr;
    struct Context
    {
        Context(sf::RenderWindow&, TextureHolder&, FontHolder&);

        sf::RenderWindow* window;
        TextureHolder* textures;
        FontHolder* fonts;
    };

public:
    State(StateStack&, Context);
    virtual ~State();

    virtual bool handleEvent(const sf::Event&) = 0;
    virtual bool update(sf::Time) = 0;
    virtual void draw() = 0;

protected:
    void requestStackPush(StatesId);
    void requestStackPop();
    void requestStackClear();

    Context getContext() const;

private:
    StateStack* m_stack;
    Context m_context;
};

#endif