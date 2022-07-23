#include "userInteraction.hpp"
#include "app.hpp"
#include "Objects/TextBox.hpp"

userInteraction userInteraction::_instance;

void userInteraction::echoText(sf::Event &event, TextBox &textbox)
{
    textbox.typedOn(event);
}