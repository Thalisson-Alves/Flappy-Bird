#ifndef STATESTACK_H
#define STATESTACK_H

#include "State.h"
#include "StateIdentifiers.h"

#include <SFML/Graphics.hpp>

#include <map>
#include <vector>
#include <functional>

class StateStack
{
public:
    enum class Action
    {
        Push,
        Pop,
        Clear
    };

public:
    explicit StateStack(State::Context);

    template<typename T>
    void registerState(StatesId);

    void handleEvent(const sf::Event&);
    void update(sf::Time);
    void draw();

    void pushState(StatesId);
    void popState();
    void clearStates();

    bool isEmpty() const;

private:
    State::Ptr createState(StatesId);
    void applyPendingChanges();

private:
    struct PendingChange
    {
        explicit PendingChange(Action, StatesId=StatesId::None);

        Action action;
        StatesId statesId;
    };
private:
    std::vector<State::Ptr> m_stack;
    std::vector<PendingChange> m_pendingChanges;

    State::Context m_context;
    std::map<StatesId, std::function<State::Ptr()>> m_factories;
};

template<typename T>
void StateStack::registerState(StatesId statesId)
{
    m_factories[statesId] = [this]()
    {
        return State::Ptr(new T(*this, m_context));
    };
}

#endif