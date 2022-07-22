#include "app.hpp"
#include "drawUtil.hpp"

constexpr float function(float x)
{
    return sin(x);
}

constexpr float func2(float x)
{
    return x * x * x;
}

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
        draw.plotFuntion(&function, sf::Color::White, 0.01f, 4, -(float)(5));
        draw.plotFuntion(&func2, sf::Color::Cyan, 0.01f, 4, -(float)(5));

        draw.drawPoint(draw.halfSize() / 200, sf::Color::Yellow, 10);
        Eigen::Vector2d pt(-5, 0);
        draw.drawPoint(pt, sf::Color::Black, 10);

        draw.drawCircle(50, sf::Color::Green, 3);

        draw.display();
        app.window.display();
    }

    return 0;
}
