#include "StateStack.h"

StateStack::StateStack(State::Context context) : m_context(context), m_stack(), m_pendingList(), m_factories()
{
}

void StateStack::handleEvent(const sf::Event& event)
{
    for (auto itr = m_stack.rbegin(); itr != m_stack.rend(); itr++) {
        if (!(*itr)->handleEvent(event))
            break;
    }

    applyPendingChanges();
}

void StateStack::update(sf::Time dt)
{
    for (auto itr = m_stack.rbegin(); itr != m_stack.rend(); itr++) {
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
    m_pendingList.push_back(PendingChanges(Action::Push, statesId));
}

void StateStack::popState()
{
    m_pendingList.push_back(PendingChanges(Action::Pop));
}

void StateStack::clearStates()
{
    m_pendingList.push_back(PendingChanges(Action::Clear));
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
    for (PendingChanges change : m_pendingList) {
        switch (change.action) {
        case StateStack::Action::Push:
            m_stack.push_back(createState(change.statesId));
            break;
        case StateStack::Action::Pop:
            m_stack.pop_back();
            break;
        case StateStack::Action::Clear:
            m_stack.clear();
        }
    }

    m_pendingList.clear();
}

StateStack::PendingChanges::PendingChanges(Action action, StatesId statesId) : action(action), statesId(statesId)
{
}