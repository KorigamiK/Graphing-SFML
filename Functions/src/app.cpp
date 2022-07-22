#include "app.hpp"

Application::Application()
{
    screenSize = sf::VideoMode::getDesktopMode();
    screenSize = sf::VideoMode(start_w, start_h, screenSize.bitsPerPixel);

    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 16;

    sf::Uint32 window_style = (sf::Style::Resize | sf::Style::Close);

    window.create(screenSize, title, window_style, settings);
    window.setFramerateLimit(60);
    window.requestFocus();
    view = window.getDefaultView();

    renderTexture.create(window.getSize().x * renderScale, window.getSize().y * renderScale, settings);

    renderTexture.setSmooth(true);
    renderTexture.setActive(true);

    // Setup OpenGL things

    glHint(GL_POINT_SMOOTH, GL_NICEST);
    glHint(GL_LINE_SMOOTH, GL_NICEST);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_SMOOTH);
}

void Application::eventHandler(sf::Event &event)
{
    static sf::FloatRect visibleArea = sf::FloatRect(0, 0, event.size.width, event.size.height);

    switch (event.type)
    {
    case sf::Event::Closed:
        window.close();
        break;

    case sf::Event::Resized:
    {
        visibleArea.width = event.size.width;
        visibleArea.height = event.size.height;
        window.setView(sf::View(visibleArea));
        renderTexture.create(window.getSize().x * renderScale, window.getSize().y * renderScale, settings);
        renderTexture.setSmooth(true);
        renderTexture.setActive(true);
        break;
    }

    case sf::Event::KeyPressed:
        switch (event.key.code)
        {
        case sf::Keyboard::Escape:
            window.close();
            break;
        default:
            break;
        }
        break;

    default:
        break;
    }
}