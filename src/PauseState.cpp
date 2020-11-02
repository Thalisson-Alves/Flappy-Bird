#include "PauseState.h"

PauseState::PauseState(StateStack& stack, State::Context context) :
    State(stack, context),
    m_text("", context.fonts->get(FontsId::Main), 16),
    m_GUIContainer(*context.window)
{
    sf::Vector2u windowSize = context.window->getSize();

    m_text.setString("Game Paused");
    m_text.setCharacterSize(60);
    centerOrigin(m_text);
    m_text.setPosition(0.5f * windowSize.x, 0.2f * windowSize.y);

    auto continueButton = std::make_shared<GUI::Button>(*context.textures, *context.fonts);
    continueButton->setPosition(0.5f * windowSize.x - 120, 0.4f * windowSize.y + 75);
    continueButton->setText("Continue");
    continueButton->scaleSprite(1.0f, 2.0f);
    continueButton->setCallback([this]()
    {
        requestStackPop();
    });

    auto backToMenuButton = std::make_shared<GUI::Button>(*context.textures, *context.fonts);
    backToMenuButton->setPosition(0.5f * windowSize.x - 120, 0.4f * windowSize.y + 125);
    backToMenuButton->setText("Back to Menu");
    backToMenuButton->scaleSprite(1.0f, 2.0f);
    backToMenuButton->setCallback([this]()
    {
        requestStackClear();
        requestStackPush(StatesId::Menu);
    });

    m_GUIContainer.pack(continueButton);
    m_GUIContainer.pack(backToMenuButton);
}

bool PauseState::handleEvent(const sf::Event& event)
{
    m_GUIContainer.handleEvent(event);

    return false;
}

bool PauseState::update(sf::Time)
{
    return false;
}

void PauseState::draw()
{
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());

    sf::RectangleShape backgroundShape;
    backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
    backgroundShape.setSize(window.getView().getSize());
    // centerOrigin(backgroundShape);
    // backgroundShape.setPosition()

    window.draw(backgroundShape);
    window.draw(m_text);
    window.draw(m_GUIContainer);
}