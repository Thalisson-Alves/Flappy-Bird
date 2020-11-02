#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "Utility.h"
#include "State.h"
#include "StateStack.h"
#include "Container.h"
#include "Button.h"

#include <SFML/Graphics.hpp>

#include <vector>

class MenuState : public State
{
public:
    MenuState(StateStack&, State::Context);

    virtual bool handleEvent(const sf::Event&);
    virtual bool update(sf::Time);
    virtual void draw();

private:
    sf::Sprite m_backgroundSprite;
    GUI::Container m_GUIContainer;
    sf::Text m_text;
};

#endif