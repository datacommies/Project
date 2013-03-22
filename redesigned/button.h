#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
struct Button {
  int id;
  sf::Vector2f position;
  sf::Vector2f size;
  sf::Text label;
  sf::RectangleShape rect;
  bool inited;
  std::string text;

  Button(int i, sf::Vector2f pos, sf::Vector2f dim, sf::Font& font, const char * tex) :
         id(i),  position(pos), size(dim), inited(false), text(tex) {
    rect.setPosition (position);

    rect.setSize (size);
    rect.setOutlineThickness(2);

    label.setPosition (position);
    label.setColor(sf::Color::Black);
  }

  bool operator== (Button & right) {
    return (id == right.id);
  }

  bool operator< (const Button & right) const {
    return (id - right.id);
  }

  void init (sf::Font& f) {
    if (!inited) {
      label.setString(text);
      label.setFont(f);
      inited = true;
    }
  }

  void draw (sf::RenderWindow& win) {
    if (!inited) {
      std::cerr << "Button not inited!" << std::endl;
    }

    sf::Vector2f mouse  = win.mapPixelToCoords(sf::Mouse::getPosition(win));// = sf::Vector2f(sf::Mouse::getPosition(win));

    if (rect.getGlobalBounds().contains(mouse))
      rect.setOutlineColor(sf::Color(100, 100, 100));

    win.draw(rect);
    win.draw(label);
  }
};