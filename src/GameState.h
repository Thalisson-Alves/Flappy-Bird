#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "StateStack.h"
#include "World.h"

#include <SFML/Graphics.hpp>

class GameState : public State
{
public:
    GameState(StateStack&, State::Context);
    
    virtual bool handleEvent(const sf::Event&);
    virtual bool update(sf::Time);
    virtual void draw();

private:
    World world;
};

#endif