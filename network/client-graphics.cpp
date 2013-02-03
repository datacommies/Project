#include <cstdio> // std
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>

#include <SFML/Graphics.hpp>

#include "types.h"

using namespace std;

void update (sf::RenderWindow& window, sf::Clock& sclock);

sf::Font MyFont;
extern vector<player_matchmaking_t> players;

void * init (void * nothing) {
    int sockfd = (long) nothing;
    sf::Clock sclock;
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

    if (!MyFont.loadFromFile("sansation.ttf")) {
        printf("error loading font\n");
    }

    while (window.isOpen()) {
        update(window, sclock);
    }
    shutdown(sockfd, SHUT_RDWR);
    close(sockfd);
    return NULL;
}

void draw_player (sf::RenderWindow& rw, int slot, player_matchmaking_t& pmt) {
    sf::Text Text(pmt.name, MyFont, 20);
    sf::RectangleShape shape(sf::Vector2f(300, 25));
    shape.setFillColor(pmt.ready ? sf::Color(0,255,0) : sf::Color(128,128,128));
    shape.setOutlineColor(sf::Color::White);
    shape.setOutlineThickness(2.0f);
    shape.setPosition(800-307, 7 + (32 * slot));
    Text.setPosition(800-200, 7+ (32 * slot));
    rw.draw(shape);
    rw.draw(Text);
}

void update (sf::RenderWindow& window, sf::Clock& sclock) {
    sf::Time elapsed = sclock.restart();
    
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
    window.clear();

    for (int i = 0; i < players.size(); ++i) {
        draw_player(window, i, players[i]);
    }

    window.display();
}