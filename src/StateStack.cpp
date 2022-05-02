#include "StateStack.h"

StateStack::StateStack(State::Context context) : m_stack(), m_pendingChanges(), m_context(context), m_factories()
{
}

void StateStack::handleEvent(const sf::Event& event)
{
    for (auto itr = m_stack.rbegin(); itr != m_stack.rend(); itr++)
    {
        if (!(*itr)->handleEvent(event))
            break;
    }

    applyPendingChanges();
}

void StateStack::update(sf::Time dt)
{
    for (auto itr = m_stack.rbegin(); itr != m_stack.rend(); itr++)
    {
        if (!(*itr)->update(dt))
            break;
    }

    applyPendingChanges();
}

void StateStack::draw()
{
    for (State::Ptr& state : m_stack)
        state->draw();
}

void StateStack::pushState(StatesId statesId)
{
    m_pendingChanges.emplace_back(Action::Push, statesId);
}

void StateStack::popState()
{
    m_pendingChanges.emplace_back(Action::Pop);
}

void StateStack::clearStates()
{
    m_pendingChanges.emplace_back(Action::Clear);
}

bool StateStack::isEmpty() const
{
    return m_stack.empty();
}

State::Ptr StateStack::createState(StatesId statesId)
{
    auto found = m_factories.find(statesId);
    if (found == m_factories.end())
        throw std::logic_error("StateStack::createState - State not registered");

    return found->second();
}

void StateStack::applyPendingChanges()
{
    for (auto pendingChange : m_pendingChanges)
    {
        switch (pendingChange.action)
        {
        case StateStack::Action::Push:
            m_stack.push_back(createState(pendingChange.statesId));
            break;
        case StateStack::Action::Pop:
            m_stack.pop_back();
            break;
        case StateStack::Action::Clear:
            m_stack.clear();
        }
    }

    m_pendingChanges.clear();
}

StateStack::PendingChange::PendingChange(Action action, StatesId statesId) : action(action), statesId(statesId)
{
}