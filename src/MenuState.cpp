#include "MenuState.h"

MenuState::MenuState(StateStack& stack, State::Context context) :
    State(stack, context),
    m_backgroundSprite(context.textures->get(TexturesId::Background)),
    m_GUIContainer(*context.window),
    m_text("Flappy Bird", context.fonts->get(FontsId::Main), 60)
{
    sf::Vector2u windowSize = context.window->getSize();

    centerOrigin(m_text);
    m_text.setPosition(0.5f * windowSize.x, 0.2f * windowSize.y);

    centerOrigin(m_backgroundSprite);
    m_backgroundSprite.setPosition(context.window->getView().getSize() / 2.0f);

    auto playButton = std::make_shared<GUI::Button>(*context.textures, *context.fonts);
    playButton->setPosition(0.5f * windowSize.x - 65, 0.4f * windowSize.y + 75);
    playButton->setText("Play");
    playButton->setToggle(true);
    playButton->setCallback([this]()
    {
        requestStackPop();
        requestStackPush(StatesId::Game);
    });

    auto exitButton = std::make_shared<GUI::Button>(*context.textures, *context.fonts);
    exitButton->setPosition(playButton->getPosition().x, playButton->getPosition().y + 50);
    exitButton->setText("Exit");
    exitButton->setCallback([this]()
    {
        requestStackPop();
    });

    m_GUIContainer.pack(playButton);
    m_GUIContainer.pack(exitButton);
}

bool MenuState::handleEvent(const sf::Event& event)
{
    m_GUIContainer.handleEvent(event);
    return false;
}

bool MenuState::update(sf::Time)
{
    return true;
}

void MenuState::draw()
{
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());

    window.draw(m_backgroundSprite);
    window.draw(m_text);
    window.draw(m_GUIContainer);
}