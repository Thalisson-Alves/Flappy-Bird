#include "State.h"
#include "StateStack.h"

State::State(StateStack& stack, Context context) : m_stack(&stack), m_context(context)
{
}

State::~State()
{
}

void State::requestStackPush(StatesId statesId)
{
    m_stack->pushState(statesId);
}

void State::requestStackPop()
{
    m_stack->popState();
}

void State::requestStackClear()
{
    m_stack->clearStates();
}

State::Context State::getContext() const
{
    return m_context;
}

State::Context::Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts) : window(&window), textures(&textures), fonts(&fonts)
{
}