#ifndef WORLD_H
#define WORLD_H

#include "Pipe.h"
#include "Bird.h"
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"

#include <SFML/Graphics.hpp>

#include <cmath>
#include <deque>
#include <memory>

class World : sf::NonCopyable
{
public:
    World(sf::RenderWindow&);

    void handleEvent(const sf::Event&);
    void update(sf::Time);
    void draw();

private:
    void loadResources();

    void spawnPipe();
    void handleCollisions();

private:
    sf::RenderWindow& m_window;
    TextureHolder m_textures;

    sf::Sprite m_backgroundSprite;
    sf::Sprite m_baseSprite;

    Bird::Ptr m_bird;
    const float m_birdSpeed;
    std::deque<Pipe::Ptr> m_pipes;
    const float m_pipeSpeed;
    const float m_spawnDistance;

    Random m_rng;
};

#endif