#include "app.hpp"
#include "drawUtil.hpp"

int main(int argc, char const *argv[])
{
    Application app;

    drawUtil draw(app);

    draw.drawAxes(sf::Color::Cyan, sf::Color::Red, 10.0);

    while (app.window.isOpen())
    {
        sf::Event event;
        while (app.window.pollEvent(event))
            app.eventHandler(event);

        draw.drawBackground(1.0);
        draw.drawAxes(sf::Color::Magenta, sf::Color::Red, 10.0);
        draw.display();
        app.window.display();
    }

    return 0;
}
