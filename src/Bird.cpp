#include "Bird.h"

Bird::Bird (const TextureHolder& textures) :
	m_sprite(textures.get(TexturesId::Bird)),
	m_state(Bird::States::None)
{
	centerOrigin(m_sprite);
}

float Bird::getWidth() const
{
	return m_sprite.getGlobalBounds().width;
}

float Bird::getHeight() const
{
	return m_sprite.getGlobalBounds().height;
}

Bird::States Bird::getState() const
{
	return m_state;
}

void Bird::setState(Bird::States state)
{
	m_state = state;
}

void Bird::update(sf::Time dt)
{
	if (m_state == Bird::States::Falling) {
		accelerate(0.0f, 20.0f);
	}
	else if (m_state == Bird::States::Flying) {
		setVelocity(0.0f, -350.0f);
		m_state = Bird::States::Falling;
	}
	Entity::update(dt);
}

sf::FloatRect Bird::getBoundingRect() const
{
	return getTransform().transformRect(m_sprite.getGlobalBounds());
}

void Bird::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_sprite, states);
}