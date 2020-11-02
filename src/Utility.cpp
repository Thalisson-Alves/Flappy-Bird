#include "Utility.h"

#include <cmath>

void centerOrigin(sf::Text& text)
{
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(std::floor(bounds.left + bounds.width / 2.0f), std::floor(bounds.top + bounds.height / 2.0f));
}

void centerOrigin(sf::Sprite& sprite)
{
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(std::floor(bounds.left + bounds.width / 2.0f), std::floor(bounds.top + bounds.height / 2.0f));
}