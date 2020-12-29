#include "GameState.h"

GameState::GameState(StateStack& stack, State::Context context) :
    State(stack, context),
    world(*context.window, *context.fonts)
{
}

bool GameState::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::LostFocus || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
        requestStackPush(StatesId::Pause);
    else
        world.handleEvent(event);
    
    return true;
}

bool GameState::update(sf::Time dt)
{
    if (world.getState() == World::States::GameOver) {
        requestStackPush(StatesId::GameOver);
        world.setState(World::States::Waiting);
    }
    else
        world.update(dt);

    return true;
}

void GameState::draw()
{
    world.draw();
}