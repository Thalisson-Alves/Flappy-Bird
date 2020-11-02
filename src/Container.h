#ifndef CONTAINER_H
#define CONTAINER_H

#include "Component.h"
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"

#include <SFML/Graphics.hpp>

#include <memory>
#include <vector>

namespace GUI
{
    class Container : public Component
    {
    public:
        typedef std::shared_ptr<Container> Ptr;

    public:
        Container(sf::Window&);

        void pack(Component::Ptr);

        virtual bool isSelectable() const;

        virtual void handleEvent(const sf::Event&);
    
    private:
        virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

        bool hasSelection() const;
        void select(std::size_t);
        void selectNext();
        void selectPrevious();

    private:
        std::vector<Component::Ptr> m_children;
        int m_selectedChild;
        sf::Window& m_window;
    };
}

#endif