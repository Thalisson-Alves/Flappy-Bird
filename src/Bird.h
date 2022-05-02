#ifndef BIRD_H
#define BIRD_H

#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include "Entity.h"
#include "Utility.h"

#include <SFML/Graphics.hpp>

#include <memory>

class Bird : public Entity
{
 public:
    typedef std::unique_ptr<Bird> Ptr;

    enum class States
    {
        Flying,
        Falling,
        None
    };

 public:
    explicit Bird(const TextureHolder&);

    float getWidth() const;
    float getHeight() const;

    Bird::States getState() const;
    void setState(Bird::States);

    sf::FloatRect getBoundingRect() const;

    void draw(sf::RenderTarget&, sf::RenderStates) const override;

 private:
    sf::Sprite m_sprite;
    Bird::States m_state;
};

#endif
