#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <cmath>
#include <random>
#include <iostream>

using namespace std;

template <typename T1, typename T2>
void plot(T1 (*f)(T2), T2 begin, T2 last, T2 step, T1 yMin, T1 yMax, sf::Color plotColor, sf::Color axisColor, sf::RenderWindow &window)
{
    T2 current = begin;
    if (axisColor != sf::Color::Transparent)
    {
        sf::RectangleShape xAxis, yAxis;
        xAxis.setSize(sf::Vector2f(window.getSize().x, 1));
        xAxis.setPosition(0, yMax / (yMax - yMin) * window.getSize().y);
        xAxis.setFillColor(axisColor);
        yAxis.setSize(sf::Vector2f(1, window.getSize().y));
        yAxis.setPosition((float)(-begin) / (last - begin) * window.getSize().x, 0);
        yAxis.setFillColor(axisColor);
        window.draw(xAxis), window.draw(yAxis);
    }
    if (step == 0)
        return;
    sf::RectangleShape v(sf::Vector2f(1, 1));
    v.setFillColor(plotColor);
    for (; current <= last; current += step)
    {
        v.setPosition((float)(current - begin) / (last - begin) * window.getSize().x,
                      (yMax - f(current)) / (yMax - yMin) * window.getSize().y);
        window.draw(v);
    }
}

template <typename T1, typename T2>
void plot(vector<pair<T1 (*)(T2), sf::Color>> fs, T2 begin, T2 last, T2 step, T1 yMin, T1 yMax, sf::Color axisColor, sf::RenderWindow &window)
{
    if (fs.size())
        plot(fs[0].first, begin, last, step, yMin, yMax, fs[0].second, axisColor, window);
    for (int i = 1; i < fs.size(); ++i)
        plot(fs[i].first, begin, last, step, yMin, yMax, fs[i].second, sf::Color::Transparent, window);
};

float timesort(int nElements)
{
    sf::Clock clock;
    std::vector<int> elements(nElements);
    std::random_device dev;
    std::mt19937 mt(dev());
    std::uniform_int_distribution<int> dist(0, 1 << 30);
    for (auto &e : elements)
        e = dist(mt);
    clock.restart();
    std::sort(elements.begin(), elements.end());
    return clock.getElapsedTime().asSeconds();
}

constexpr float customPlotFunction(float x)
{
    return 1 / x;
}

int main(int argc, char const *argv[])
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Math Functions");

redraw:
    cout << "redraw" << endl;
    window.clear(sf::Color::Black);
    plot((vector<pair<float (*)(float), sf::Color>>){
             {&sin, sf::Color::Green},
             {&exp, sf::Color::Blue},
             {&tgamma, sf::Color::Magenta},
             {&log, sf::Color::Red},
             {&customPlotFunction, sf::Color::White},
         },
         -5.0f, 5.0f, 0.01f, -20.0f, 20.0f, sf::Color::White, window);
    window.display();

    while (window.isOpen())
    {
        sf::sleep(sf::milliseconds(300));
        sf::Event event;
        while (window.pollEvent(event))
            switch (event.type)
            {
            case sf::Event::Resized:
                window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
                goto redraw;

            case sf::Event::Closed:
                window.close();
                break;
            }
    }

    sf::RenderWindow window2(sf::VideoMode::getDesktopMode(), "Vector sort times");

redraw2:
    window2.clear(sf::Color::Black);
    plot(&timesort, 100, 100000, 100, .0f, 0.01f, sf::Color::Magenta, sf::Color::Transparent, window2);
    window2.display();
    while (window2.isOpen())
    {
        // sf::sleep(sf::milliseconds(30));
        sf::Event event;
        while (window2.pollEvent(event))
            switch (event.type)
            {
            case sf::Event::Resized:
                window2.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
                goto redraw2;
            case sf::Event::Closed:
                window2.close();
            }
    }
    return 0;
}
