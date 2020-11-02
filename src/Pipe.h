#ifndef PIPE_H
#define PIPE_H

#include "Random.h"
#include "Utility.h"
#include "Entity.h"
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"

#include <SFML/Graphics.hpp>

#include <memory>
#include <utility>

class Pipe : public Entity
{
public:
	typedef std::unique_ptr<Pipe> Ptr;

public:
	Pipe(const TextureHolder& texture);

	float getWidth() const;
	float getHeight() const;

	std::pair<sf::FloatRect, sf::FloatRect> getBoundingRects() const;

	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
	
private:
	sf::Sprite m_topSprite;
	sf::Sprite m_bottomSprite;
};

#endif
