#pragma once
#include "app.hpp"
#include <Eigen/Dense>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>

class drawUtil
{
    Application &application;
    sf::RenderTexture &renderTexture;
    Eigen::Vector2d center = Eigen::Vector2d::Zero();
    long double scale = 100.0l;

    static double smoothBounce(long double t, long double trigger_t, long double a);

public:
    auto display() { return renderTexture.display(); }

    static sf::Vector2f toSF(const Eigen::Vector2d &v)
    {
        return sf::Vector2f((float)v.x(), (float)v.y());
    }

    inline Eigen::Vector2d halfSize()
    {
        return Eigen::Vector2d((double)application.window.getSize().x, (double)application.window.getSize().y) * 0.5;
    }

    void DrawAxes(const sf::Color &color1, const sf::Color &color2, double thickness)
    {
        const auto &window = application.window;
        const int min_x = int(center.x() - 0.5 * double(window.getSize().x) / scale) - 1;
        const int max_x = int(center.x() + 0.5 * double(window.getSize().x) / scale) + 1;
        const int min_y = int(center.y() - 0.5 * double(window.getSize().y) / scale) - 1;
        const int max_y = int(center.y() + 0.5 * double(window.getSize().y) / scale) + 1;

        const Eigen::Vector2d ay((double)0, (double)min_y);
        const Eigen::Vector2d by(0, (double)max_y);
        DrawLine(ay, by, color1, false, thickness);

        const Eigen::Vector2d ax((double)min_x, 0);
        const Eigen::Vector2d bx((double)max_x, 0);
        DrawLine(ax, bx, color2, false, thickness);
    }

    void DrawLine(const Eigen::Vector2d &_a, const Eigen::Vector2d &_b, const sf::Color &color, bool extend, double thickness)
    {
        std::vector<sf::Vertex> vertex_array(2);
        Eigen::Vector2d a, b;
        if (extend)
        {
            a = _a + (_a - _b).normalized() * 100.0;
            b = _b + (_b - _a).normalized() * 100.0;
        }
        else
        {
            a = _a;
            b = _b;
        }
        vertex_array[0] = sf::Vertex(toSF((a - center) * scale + halfSize()), color);
        vertex_array[1] = sf::Vertex(toSF((b - center) * scale + halfSize()), color);
        glLineWidth((float)thickness * application.renderScale);
        application.window.draw(vertex_array.data(), vertex_array.size(), sf::PrimitiveType::Lines);
    }

    void drawBackground(double thickness);

    inline drawUtil(Application &app) : application(app), renderTexture(app.renderTexture){};
};