#ifndef WORLD_H
#define WORLD_H

#include "Utility.h"
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
    enum class States
    {
        Waiting,
        Running,
        GameOver
    };

public:
    World(sf::RenderWindow&, FontHolder&);

    void handleEvent(const sf::Event&);
    void update(sf::Time);
    void draw();

    World::States getState() const;
    void setState(World::States);

private:
    void loadResources();

    void spawnPipe();
    void handleCollisions();

    void resetEntitiesPositions();
    void respawnPipeOutsideView();
    void correctBirdPosition();
    void correctBasePosition();

    void updateScore();
    void respawnAllPipes();

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
    const float m_gravity;

    World::States m_state;

    int m_score;
    sf::Text m_textScore;
};

#endif