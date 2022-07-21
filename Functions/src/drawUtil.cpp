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
                DrawLine(a, b, sf::Color::White, false, 2.0 * bounce);
            }
            else
            {
                DrawLine(a, b, sf::Color(255, 255, 255, 128), false, bounce);
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
                DrawLine(a, b, sf::Color::White, false, 2.0 * bounce);
            }
            else
            {
                DrawLine(a, b, sf::Color(255, 255, 255, 128), false, bounce);
            }
        }
    }
}
