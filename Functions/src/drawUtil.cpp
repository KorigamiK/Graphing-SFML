#include "drawUtil.hpp"

auto drawUtil::smoothBounce(long double t, long double trigger_t, long double a) -> double
{
    return std::max(1.0 + a * (1.0 - t) * std::exp(10 * (trigger_t - t)) * (1.0 - std::exp(trigger_t - t)), 0.0l);
}

auto drawUtil::drawBackground(double t) -> void
{
    auto &window = application.window;
    const int min_x = int(center.x() - 0.5 * double(window.getSize().x) / scale) - 1;
    const int max_x = int(center.x() + 0.5 * double(window.getSize().x) / scale) + 1;
    const int min_y = int(center.y() - 0.5 * double(window.getSize().y) / scale) - 1;
    const int max_y = int(center.y() + 0.5 * double(window.getSize().y) / scale) + 1;

    window.clear(sf::Color(0, 42, 77));

    for (int x = min_x; x < max_x; ++x)
    {
        for (int i = 0; i < 4; ++i)
        {
            const double q = 0.25 * double((x - min_x) * 4 + i) / double(max_x - min_x);
            const double bounce = smoothBounce(t, q * 0.5 + 0.5, 20.0);
            if (bounce <= 0.0)
            {
                continue;
            }
            const Eigen::Vector2d a((double)x + i * 0.25, (double)min_y);
            const Eigen::Vector2d b((double)x + i * 0.25, (double)max_y);
            if (i == 0)
            {
                drawLine(a, b, sf::Color::White, false, 2.0 * bounce);
            }
            else
            {
                drawLine(a, b, sf::Color(255, 255, 255, 128), false, bounce);
            }
        }
    }
    for (int y = min_y; y < max_y; ++y)
    {
        for (int i = 0; i < 4; ++i)
        {
            const double q = 0.25 * double((y - min_y) * 4 + i) / double(max_y - min_y);
            const double bounce = smoothBounce(t, q * 0.5, 20.0);
            if (bounce <= 0.0)
            {
                continue;
            }
            const Eigen::Vector2d a((double)min_x, (double)y + i * 0.25);
            const Eigen::Vector2d b((double)max_x, (double)y + i * 0.25);
            if (i == 0)
            {
                drawLine(a, b, sf::Color::White, false, 2.0 * bounce);
            }
            else
            {
                drawLine(a, b, sf::Color(255, 255, 255, 128), false, bounce);
            }
        }
    }
}

void drawUtil::drawLine(const Eigen::Vector2d &_a, const Eigen::Vector2d &_b, const sf::Color &color, bool extend, double thickness)
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

void drawUtil::drawAxes(const sf::Color &color1, const sf::Color &color2, double thickness)
{
    const auto &window = application.window;
    const int min_x = int(center.x() - 0.5 * double(window.getSize().x) / scale) - 1;
    const int max_x = int(center.x() + 0.5 * double(window.getSize().x) / scale) + 1;
    const int min_y = int(center.y() - 0.5 * double(window.getSize().y) / scale) - 1;
    const int max_y = int(center.y() + 0.5 * double(window.getSize().y) / scale) + 1;

    const Eigen::Vector2d ay((double)0, (double)min_y);
    const Eigen::Vector2d by(0, (double)max_y);
    drawLine(ay, by, color1, false, thickness);

    const Eigen::Vector2d ax((double)min_x, 0);
    const Eigen::Vector2d bx((double)max_x, 0);
    drawLine(ax, bx, color2, false, thickness);
}

void drawUtil::drawPoint(const Eigen::Vector2d &c, const sf::Color &color, double radius)
{
    sf::CircleShape circle((float)radius * application.renderScale);
    circle.setOrigin(circle.getRadius(), circle.getRadius());
    circle.setFillColor(color);
    circle.setPosition(toSF((c - center) * scale + halfSize()));
    application.window.draw(circle);
}

void drawUtil::drawCircle(float radius, const sf::Color &colour, float thickness)
{
    sf::CircleShape circle(float(radius), 50);
    circle.setOrigin(circle.getRadius(), circle.getRadius());
    circle.setFillColor(sf::Color::Transparent);
    circle.setOutlineColor(colour);
    circle.setOutlineThickness((float)thickness);
    circle.setPosition(toSF((center - center) * scale + halfSize()));
    application.window.draw(circle);
}