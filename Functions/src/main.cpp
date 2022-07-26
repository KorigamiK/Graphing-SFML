#include "Objects/TextBox.hpp"
#include "app.hpp"
#include "drawUtil.hpp"

constexpr float function(float x) { return sin(x); }

constexpr float func2(float x) { return log(x); }

int main(int argc, char const *argv[])
{
  Application &app = Application::get();

  auto &draw = drawUtil::get();
  // draw.drawAxes(sf::Color::Cyan, sf::Color::Red, 10.0);

  app.watchTextInput = true;

  TextBox textbox(30, sf::Color::Black, true, {200, 100});

  while (app.window.isOpen())
  {
    sf::Event event;
    while (app.window.pollEvent(event))
      app.eventHandler(event, textbox);

    app.renderTexture.clear();
    app.window.clear();

    draw.drawBackground(1.0);

    draw.drawAxes(sf::Color(150, 150, 150), sf::Color(150, 150, 150), 6.0);
    draw.plotFuntion(&function, sf::Color(37, 44, 69), 0.01f, 4, -(float)(5));
    draw.plotFuntion(&func2, sf::Color(154, 141, 192), 0.01f, 4, -(float)(5));

    draw.drawPoint(draw.halfSize() / 200, sf::Color::Yellow, 10);
    Eigen::Vector2d pt(50, 0);
    draw.drawPoint(pt, sf::Color::Black, 10);

    draw.drawCircle(50, sf::Color(99, 176, 156), 3);
    textbox.draw();
    app.window.display();
  }

  return 0;
}
