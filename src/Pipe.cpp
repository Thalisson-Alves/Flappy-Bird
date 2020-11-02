#include "Pipe.h"

Pipe::Pipe(const TextureHolder& textures) :
	m_topSprite(textures.get(TexturesId::Pipe)),
	m_bottomSprite(textures.get(TexturesId::Pipe))
{
	centerOrigin(m_topSprite);
	centerOrigin(m_bottomSprite);
	m_topSprite.rotate(180.0f);
	m_topSprite.scale(-1.0f, 1.0f);
	m_bottomSprite.setPosition(m_bottomSprite.getPosition().x, 440.0f);
}

float Pipe::getWidth() const
{
	return m_bottomSprite.getGlobalBounds().width;
}

float Pipe::getHeight() const
{
	return m_bottomSprite.getGlobalBounds().height;
}

std::pair<sf::FloatRect, sf::FloatRect> Pipe::getBoundingRects() const
{
	auto topRect = getTransform().transformRect(m_topSprite.getGlobalBounds());
	auto bottomRect = getTransform().transformRect(m_bottomSprite.getGlobalBounds());
	return std::make_pair(topRect, bottomRect);
}

void Pipe::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_topSprite, states);
	target.draw(m_bottomSprite, states);
}
