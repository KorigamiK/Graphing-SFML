#include "app.hpp"

Application Application::_instance;

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

    // Load fonts

    if (!textFont.loadFromFile("./res/terminal.otf"))
        std::cerr << "Error loading font\n";
}

void Application::eventHandler(sf::Event &event, TextBox &textbox)
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
        case sf::Keyboard::Pause:
            window.close();
            break;
        default:
            break;
        }
        break;

    case sf::Event::TextEntered:
        if (event.text.unicode < 128)
        {
            textInputString += static_cast<char>(event.text.unicode);
            if (event.text.unicode == ENTER_KEY)
                textbox.setSelected(true);
            else if (event.text.unicode == ESCAPE_KEY)
                textbox.setSelected(false);
            userInteraction::get().echoText(event, textbox);
        }
    default:
        break;
    }
}