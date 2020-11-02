#ifndef COMPONENT_H 
#define COMPONENT_H

#include <SFML/Graphics.hpp>

#include <memory>

namespace GUI
{
    class Component : public sf::Drawable, public sf::Transformable, private sf::NonCopyable
    {
    public:
        typedef std::shared_ptr<Component> Ptr;

    public:
        Component();
        virtual ~Component();

        virtual bool isSelectable() const = 0;

        virtual void select();
        virtual void deselect();
        bool isSelected() const;

        virtual void activate();
        virtual void deactivate();
        bool isActive() const;

        virtual void handleEvent(const sf::Event&) = 0;
        virtual bool isMouseOver(const sf::Window&) const;

    private:
        bool m_isSelected;
        bool m_isActive;
    };
}

#endif