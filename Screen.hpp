#ifndef SCREEN_H
#define SCREEN_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace cardgame{
    class Screen{
    public:
        virtual int Run (sf::RenderWindow &rwin) = 0;
    };
}
#endif // SCREEN_H
