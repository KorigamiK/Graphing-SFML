#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <exprtk.hpp>

#include "Objects/TextBox.hpp"
// User interaction singleton class
class userInteraction
{
private:
    static userInteraction _instance;
    userInteraction() {}

public:
    static userInteraction &get() { return _instance; }
    userInteraction(const userInteraction &) = delete;

    void echoText(sf::Event &event, TextBox &textbox);
};