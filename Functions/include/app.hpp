#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>

#include "userInteraction.hpp"
#include "Objects/TextBox.hpp"

// Singleton application
class Application
{
private:
    Application();

    static Application _instance;

    sf::VideoMode screenSize;
    sf::ContextSettings settings;
    sf::View view;

    static const int start_w = 480, start_h = 360;
    constexpr static const float renderScale = 0.5f;
    const char *title = "Test SFML - By KorigamiK";

public:
    bool watchTextInput = false;
    std::string textInputString = "";
    sf::Font textFont;

    Application(const Application &) = delete;

    friend class drawUtil;

    static Application &get() { return _instance; };

    sf::RenderWindow window;
    sf::RenderTexture renderTexture; // renderer

    void eventHandler(sf::Event &event, TextBox &textbox);

    inline ~Application() { std::cout << "Destroyed app" << std::endl; }
};