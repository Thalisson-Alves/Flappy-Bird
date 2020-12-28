#include "GameOverState.h"

GameOverState::GameOverState(StateStack& stack, State::Context context) :
    State(stack, context),
    m_backgroundSprite(context.textures->get(TexturesId::Background)),
    m_GUIContainer(*context.window),
    m_text("Game Over", context.fonts->get(FontsId::Main), 60)
{
    sf::Vector2u windowSize = context.window->getSize();

    centerOrigin(m_text);
    m_text.setPosition(0.5f * windowSize.x, 0.2f * windowSize.y);

    centerOrigin(m_backgroundSprite);
    m_backgroundSprite.setPosition(context.window->getView().getSize() / 2.0f);

    auto restartButton = std::make_shared<GUI::Button>(*context.textures, *context.fonts);
    restartButton->setPosition(0.5f * windowSize.x - 120, 0.4f * windowSize.y + 75);
    restartButton->setText("Restart");
    restartButton->scaleSprite(1.0f, 2.0f);
    restartButton->setCallback([this]()
    {
        requestStackPop();
    });

    auto menuButton = std::make_shared<GUI::Button>(*context.textures, *context.fonts);
    menuButton->setPosition(restartButton->getPosition().x, restartButton->getPosition().y + 50);
    menuButton->setText("Main Menu");
    menuButton->scaleSprite(1.0f, 2.0f);
    menuButton->setCallback([this]()
    {
        requestStackClear();
        requestStackPush(StatesId::Menu);
    });

    m_GUIContainer.pack(restartButton);
    m_GUIContainer.pack(menuButton);
}

bool GameOverState::handleEvent(const sf::Event& event)
{
    m_GUIContainer.handleEvent(event);
    return false;
}

bool GameOverState::update(sf::Time)
{
    return false;
}

void GameOverState::draw()
{
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());

    window.draw(m_backgroundSprite);
    window.draw(m_text);
    window.draw(m_GUIContainer);
}