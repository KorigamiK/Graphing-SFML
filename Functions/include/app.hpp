#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>

class Application
{
private:
    sf::VideoMode screenSize;
    sf::ContextSettings settings;
    sf::View view;
    sf::RenderTexture renderTexture; // renderer

    static const int start_w = 480, start_h = 360;
    constexpr static const float renderScale = 0.5f;
    const char *title = "Test SFML - By KorigamiK";

public:
    friend class drawUtil;

    sf::RenderWindow window;

    Application();

    void eventHandler(sf::Event &event);

    inline ~Application() { std::cout << "Destroyed app" << std::endl; }
};