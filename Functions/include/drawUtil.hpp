#pragma once
#include "app.hpp"
#include <Eigen/Dense>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>

class drawUtil
{
private:
    Application &application;
    sf::RenderTexture &renderTexture;
    Eigen::Vector2d center = Eigen::Vector2d::Zero();
    long double scale = 100.0l;

    static double smoothBounce(long double t, long double trigger_t, long double a);

    inline static sf::Vector2f toSF(const Eigen::Vector2d &v) { return sf::Vector2f(v.x(), v.y()); }

    inline Eigen::Vector2d halfSize() { return Eigen::Vector2d(application.window.getSize().x, application.window.getSize().y) * 0.5; }

public:
    inline drawUtil(Application &app) : application(app), renderTexture(app.renderTexture){};

    auto display() { return renderTexture.display(); }

    void drawAxes(const sf::Color &color1, const sf::Color &color2, double thickness);

    void drawLine(const Eigen::Vector2d &_a, const Eigen::Vector2d &_b, const sf::Color &color, bool extend, double thickness);

    void drawBackground(double thickness);

    template <typename TDomain, typename TRange>
    auto plotFuntion(TDomain (*function)(TRange))
    {
        return;
    }
};