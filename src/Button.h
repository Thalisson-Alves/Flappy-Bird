#ifndef BUTTON_H
#define BUTTON_H

#include "Component.h"
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include "Utility.h"

#include <SFML/Graphics.hpp>

#include <memory>
#include <functional>

namespace GUI
{
    class Button : public Component
    {
    public:
        typedef std::shared_ptr<Button> Ptr;

    public:
        Button(const TextureHolder&, const FontHolder&);

        void setCallback(std::function<void()>);
        void setText(const std::string&);
        void setToggle(bool);

        void scaleSprite(float, float);

        virtual bool isSelectable() const;

        virtual void select();
        virtual void deselect();

        virtual void activate();
        virtual void deactivate();

        virtual void handleEvent(const sf::Event&);

        virtual bool isMouseOver(const sf::Window&) const;

    private:
        virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

    private:
        std::function<void()> m_callback;

        const sf::Texture& m_normalTexture;
        const sf::Texture& m_selectedTexture;
        const sf::Texture& m_pressedTexture;

        sf::Sprite m_sprite;
        sf::Text m_text;

        bool m_isToggle;
    };
}

#endif