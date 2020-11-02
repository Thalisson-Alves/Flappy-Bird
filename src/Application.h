#ifndef APPLICATION_H
#define APPLICATION_H

#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include "StateStack.h"
#include "MenuState.h"
#include "GameState.h"
#include "PauseState.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Application
{
public:
    Application();

    void run();

private:
    void handleEvent();
    void update(sf::Time);
    void draw();

    void registerStates();

private:
    const sf::Time m_timePerFrame;

    sf::RenderWindow m_window;
    TextureHolder m_textures;
    FontHolder m_fonts;

    StateStack m_stateStack;
};

#endif