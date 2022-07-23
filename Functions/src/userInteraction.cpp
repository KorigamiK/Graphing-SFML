#include "userInteraction.hpp"

#include "app.hpp"

userInteraction userInteraction::_instance;

void userInteraction::echoText()
{
    std::cout << Application::get().textInputString;
}