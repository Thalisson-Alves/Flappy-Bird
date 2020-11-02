#include "Button.h"

namespace GUI
{
    Button::Button(const TextureHolder& textures, const FontHolder& fonts) : 
        m_callback(),
        m_normalTexture(textures.get(TexturesId::ButtonNormal)),
        m_selectedTexture(textures.get(TexturesId::ButtonPressed)),
        m_pressedTexture(textures.get(TexturesId::ButtonSelected)),
        m_sprite(),
        m_text("", fonts.get(FontsId::Main), 30),
        m_isToggle(false)
    {
        m_sprite.setTexture(m_normalTexture);
        m_sprite.scale(3.0f, 3.0f);

        centerOrigin(m_text);
        sf::FloatRect bounds = m_sprite.getLocalBounds();
        m_text.setPosition(bounds.width, 0);
    }

    void Button::setCallback(std::function<void()> callback)
    {
        m_callback = std::move(callback);
    }

    void Button::setText(const std::string& text)
    {
        m_text.setString(text);
    }

    void Button::setToggle(bool flag)
    {
        m_isToggle = flag;
    }

    void Button::scaleSprite(float scaleY, float scaleX)
    {
        m_sprite.scale(scaleX, scaleY);
    }

    bool Button::isSelectable() const
    {
        return true;
    }

    void Button::select()
    {
        Component::select();

        m_sprite.setTexture(m_selectedTexture);
    }

    void Button::deselect()
    {
        Component::deselect();

        m_sprite.setTexture(m_normalTexture);
    }

    void Button::activate()
    {
        Component::activate();

        if (m_isToggle)
            m_sprite.setTexture(m_pressedTexture);

        if (m_callback)
            m_callback();

        if (!m_isToggle)
            deactivate();
    }

    void Button::deactivate()
    {
        Component::deactivate();

        if (m_isToggle) {
            if (isSelected())
                m_sprite.setTexture(m_selectedTexture);
            else
                m_sprite.setTexture(m_normalTexture);
        }
    }

    void Button::handleEvent(const sf::Event&)
    {
    }

    bool Button::isMouseOver(const sf::Window& window) const
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::FloatRect bounds = m_sprite.getGlobalBounds();
        sf::Vector2f position = getPosition();
        return sf::FloatRect(position.x, position.y, bounds.width, bounds.height).contains(mousePos.x, mousePos.y);
    }

    void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();

        target.draw(m_sprite, states);
        target.draw(m_text, states);
    }
}