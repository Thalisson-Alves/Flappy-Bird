#ifndef PAUSESTATE_H
#define PAUSESTATE_H

#include "State.h"
#include "StateStack.h"
#include "Utility.h"
#include "Container.h"
#include "Button.h"

#include <SFML/Graphics.hpp>

#include <memory>

class PauseState : public State
{
public:
    PauseState(StateStack&, State::Context);

    virtual bool handleEvent(const sf::Event&);
    virtual bool update(sf::Time);
    virtual void draw();

private:
    sf::Text m_text;
    GUI::Container m_GUIContainer;
};

#endif