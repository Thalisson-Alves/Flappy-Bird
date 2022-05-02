#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

class Entity : public sf::Drawable, public sf::Transformable, public sf::NonCopyable
{
 public:
    void setVelocity(sf::Vector2f);
    void setVelocity(float, float);
    sf::Vector2f getVelocity() const;

    void accelerate(sf::Vector2f);
    void accelerate(float, float);

    virtual void update(sf::Time);

 private:
    void draw(sf::RenderTarget&, sf::RenderStates) const override;

    sf::Vector2f m_velocity;
};

#endif