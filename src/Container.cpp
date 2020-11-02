#include "Container.h"

namespace GUI
{
    Container::Container(sf::Window& window) :
        m_children(),
        m_selectedChild(-1),
        m_window(window)
    {
    }

    void Container::pack(Component::Ptr component)
    {
        m_children.push_back(component);

        if (!hasSelection() && component->isSelectable())
            select(m_children.size() - 1);
    }

    bool Container::isSelectable() const
    {
        return false;
    }

    void Container::handleEvent(const sf::Event& event)
    {
        if (hasSelection() && m_children[m_selectedChild]->isActive())
            m_children[m_selectedChild]->handleEvent(event);
        else if (event.type == sf::Event::KeyReleased) {
            switch (event.key.code) {
            case sf::Keyboard::Up:
            case sf::Keyboard::W:
                selectPrevious();
                break;
            case sf::Keyboard::Down:
            case sf::Keyboard::S:
                selectNext();
                break;
            case sf::Keyboard::Return:
            case sf::Keyboard::Space:
                if (hasSelection())
                    m_children[m_selectedChild]->activate();
            }
        }
        else if (event.type == sf::Event::MouseMoved) {
            for (std::size_t i = 0; i < m_children.size(); i++) {
                if (m_children[i]->isMouseOver(m_window))
                    select(i);
            }
        }
        else if (event.type == sf::Event::MouseButtonReleased) {
            if (hasSelection()) {
                if (m_children[m_selectedChild]->isMouseOver(m_window))
                    m_children[m_selectedChild]->activate();
            }
        }
    }

    void Container::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();

        for (const Component::Ptr& child : m_children)
            target.draw(*child, states);
    }

    bool Container::hasSelection() const
    {
        return m_selectedChild >= 0;
    }

    void Container::select(std::size_t index)
    {
        if (m_children[index]->isSelectable()) {
            if (hasSelection())
                m_children[m_selectedChild]->deselect();

            m_selectedChild = index;
            m_children[m_selectedChild]->select();
        }
    }

    void Container::selectNext()
    {
        if (!hasSelection())
            return;
        
        int next = m_selectedChild;
        do
            next = (next + 1) % m_children.size();
        while (!m_children[next]->isSelectable());

        select(next);
    }

    void Container::selectPrevious()
    {
        if (!hasSelection())
            return;
        
        int prev = m_selectedChild;
        do
            prev = (m_children.size() + prev - 1) % m_children.size();
        while (!m_children[prev]->isSelectable());

        select(prev);
    }
}