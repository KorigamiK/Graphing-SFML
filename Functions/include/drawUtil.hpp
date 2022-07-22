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

    static double smoothBounce(long double t, long double trigger_t, long double a);

    inline static sf::Vector2f toSF(const Eigen::Vector2d &v) { return sf::Vector2f(v.x(), v.y()); }

public:
    long double scale = 100.0l;

    inline drawUtil(Application &app) : application(app), renderTexture(app.renderTexture){};

    inline Eigen::Vector2d halfSize() { return Eigen::Vector2d(application.window.getSize().x, application.window.getSize().y) * 0.5; }

    auto display() { return renderTexture.display(); }

    void drawAxes(const sf::Color &color1, const sf::Color &color2, double thickness);

    void drawLine(const Eigen::Vector2d &_a, const Eigen::Vector2d &_b, const sf::Color &color, bool extend, double thickness);

    void drawBackground(double thickness);

    template <typename TDomain, typename TRange>
    void plotFuntion(TRange (*function)(TDomain), const sf::Color colour, TDomain step = 0.01, double thickness = 2.0, TDomain begin = 0)
    {
        static const int NUM_PTS = 800;
        std::vector<sf::Vertex> vertex_array(NUM_PTS + 1);

        TDomain x;
        int i;

        for (x = begin, i = 0; i < vertex_array.size(); x += step, i++)
        {
            Eigen::Vector2d point(x, -function(x));
            auto offset = toSF((point - center) * scale + halfSize());
            // offset.y *= -1;
            vertex_array[i] = sf::Vertex(offset, colour);
        }
        glLineWidth((float)thickness * application.renderScale);
        application.window.draw(vertex_array.data(), vertex_array.size(), sf::PrimitiveType::LineStrip);
    }

    void drawPoint(const Eigen::Vector2d &c, const sf::Color &color, double radius = 1);

    void drawCircle(float radius, const sf::Color &colour, float thickness = 2);
};