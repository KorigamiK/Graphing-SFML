#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

// User interaction singleton class
class userInteraction
{
private:
    static userInteraction _instance;
    userInteraction() {}

public:
    static userInteraction &get() { return _instance; }
    userInteraction(const userInteraction &) = delete;

    void echoText();
};