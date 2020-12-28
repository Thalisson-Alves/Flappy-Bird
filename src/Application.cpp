#include "Application.h"

Application::Application() :
    m_window(sf::VideoMode(288, 480), "Flappy Bird AI", sf::Style::Close),
    m_fonts(),
    m_textures(),
    m_stateStack(State::Context(m_window, m_textures, m_fonts)),
    m_timePerFrame(sf::seconds(1.0f / 60.0f))
{
    m_window.setKeyRepeatEnabled(false);

    m_textures.load(TexturesId::Background, "../Media/Textures/Background.png");
    m_textures.load(TexturesId::PlayButton, "../Media/Textures/PlayButton.png");
    m_textures.load(TexturesId::ButtonNormal, "../Media/Textures/ButtonNormal.png");
    m_textures.load(TexturesId::ButtonPressed, "../Media/Textures/ButtonPressed.png");
    m_textures.load(TexturesId::ButtonSelected, "../Media/Textures/ButtonSelected.png");

    m_fonts.load(FontsId::Main, "../Media/flappy-bird-regular.ttf");

    registerStates();
    
    m_stateStack.pushState(StatesId::Menu);
}

void Application::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (m_window.isOpen()) {
        sf::Time dt = clock.restart();
        timeSinceLastUpdate += dt;
        while (timeSinceLastUpdate > m_timePerFrame) {
            timeSinceLastUpdate -= m_timePerFrame;

            handleEvent();
            update(m_timePerFrame);

            if (m_stateStack.isEmpty())
                m_window.close();
        }
        draw();
    }
}

void Application::handleEvent()
{
    sf::Event event;
    while (m_window.pollEvent(event)) {
        m_stateStack.handleEvent(event);

        if (event.type == sf::Event::Closed)
            m_window.close();
    }
}

void Application::update(sf::Time dt)
{
    m_stateStack.update(dt);
}

void Application::draw()
{
    m_window.clear();

    m_stateStack.draw();

    m_window.display();
}

void Application::registerStates()
{
    m_stateStack.registerState<MenuState>(StatesId::Menu);
    m_stateStack.registerState<PauseState>(StatesId::Pause);
    m_stateStack.registerState<GameState>(StatesId::Game);
    m_stateStack.registerState<GameOverState>(StatesId::GameOver);
}