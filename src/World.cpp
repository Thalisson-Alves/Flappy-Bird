#include "World.h"

World::World(sf::RenderWindow& window) :
    m_window(window),
    m_textures(),
    m_bird(),
    m_birdSpeed(-350.0f),
    m_spawnDistance(150.0f),
    m_pipes(),
    m_pipeSpeed(-40.0f),
    m_rng()
{
    loadResources();
    m_bird = Bird::Ptr(new Bird(m_textures));
    m_bird->setPosition(window.getSize().x / 3.0f, window.getSize().y / 2.0f);

    m_backgroundSprite.setTexture(m_textures.get(TexturesId::Background));
    centerOrigin(m_backgroundSprite);
    m_backgroundSprite.setPosition(window.getDefaultView().getSize() / 2.0f);

    m_baseSprite.setTexture(m_textures.get(TexturesId::Base));
    m_baseSprite.setPosition(m_backgroundSprite.getGlobalBounds().left, m_window.getSize().y - 50.0f);

    // Spawn 3 pipes
    for (int i = 0; i < 3; i++) {
        spawnPipe();
    }
}

void World::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space))
        m_bird->setState(Bird::States::Flying);
}

void World::update(sf::Time dt)
{
    if (m_bird->getState() == Bird::States::None)
        return;

    // update bird
    m_bird->update(dt);
    
    // update pipes
    for (Pipe::Ptr& pipe : m_pipes) {
        pipe->update(dt);
    }

    handleCollisions();
    
    // update base
    m_baseSprite.move(m_pipeSpeed * dt.asSeconds(), 0.0f);

    // Correct bird's position
    sf::Vector2f birdPos = m_bird->getPosition();
    birdPos.y = std::min(birdPos.y, m_baseSprite.getGlobalBounds().top - m_bird->getHeight() / 2.0f);
    birdPos.y = std::max(birdPos.y, m_bird->getHeight() / 2.0f);
    m_bird->setPosition(birdPos);

    // Destroy pipe outside the map and spawn one more
    sf::FloatRect bgBounds = m_backgroundSprite.getGlobalBounds();
    if (m_pipes[0]->getPosition().x + m_pipes[0]->getWidth() / 2.0f <= bgBounds.left) {
        m_pipes.pop_front();
        spawnPipe();
    }

    // Correct base position
    sf::Vector2f basePos = m_baseSprite.getPosition();
    if (basePos.x <= bgBounds.left + (bgBounds.width - m_baseSprite.getLocalBounds().width))
        basePos.x = bgBounds.left;
    m_baseSprite.setPosition(basePos);
}

void World::draw()
{
    m_window.draw(m_backgroundSprite);

    for (Pipe::Ptr& pipe : m_pipes)
        m_window.draw(*pipe);
    
    m_window.draw(*m_bird);
    
    m_window.draw(m_baseSprite);
}

void World::spawnPipe()
{
    auto pipe = Pipe::Ptr(new Pipe(m_textures));
    pipe->setVelocity(m_pipeSpeed, 0.0f);
    float padding = m_window.getView().getSize().y / 2.0f - 100.0f;
    float yOffset = m_rng.getFloat(-padding, padding);
    if (!m_pipes.empty())
        pipe->setPosition(m_pipes.back()->getPosition().x + m_spawnDistance, yOffset);
    else {
        pipe->setPosition(m_window.getSize().x + pipe->getWidth(), yOffset);
    }
    
    m_pipes.push_back(std::move(pipe));
}

void World::handleCollisions()
{
    for (auto& pipe : m_pipes) {
        auto rects = pipe->getBoundingRects();
        if (m_bird->getBoundingRect().intersects(rects.first) || m_bird->getBoundingRect().intersects(rects.second)) {
            m_bird->setState(Bird::States::None);
            break;
        }
    }
}

void World::loadResources()
{
    m_textures.load(TexturesId::Bird, "../Media/Textures/Bird1.png");
    m_textures.load(TexturesId::Pipe, "../Media/Textures/Pipe.png");
    m_textures.load(TexturesId::Background, "../Media/Textures/Background.png");
    m_textures.load(TexturesId::Base, "../Media/Textures/Base.png");
}