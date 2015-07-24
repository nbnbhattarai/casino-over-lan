#ifndef GUESSPOINT_H
#define GUESSPOINT_H
#include "Screen.hpp"

class GuessPointScreen : cardgame::Screen {
public:
    virtual int Run (sf::RenderWindow &App);
};

int GuessPointScreen::Run(sf::RenderWindow &App){
    bool running = true;
    sf::Event event;
    std::string point;

    sf::Text txtPoint;
    sf::Text caption;
    sf::RectangleShape mainR;
    sf::RectangleShape Titlebar;

    mainR.setSize(sf::Vector2f(240,120));
    mainR.setPosition(562,323);
    mainR.setFillColor(sf::Color::Green);
    mainR.setOutlineThickness(1);
    mainR.setOutlineColor(sf::Color::Black);

    Titlebar.setSize(sf::Vector2f(240,30));
    Titlebar.setPosition(562,323);
    Titlebar.setFillColor(sf::Color::Green);
    Titlebar.setOutlineColor(sf::Color::Black);
    Titlebar.setOutlineThickness(1);

    txtPoint.setCharacterSize(25);
    txtPoint.setPosition(652,384);
    txtPoint.setColor(sf::Color::Black);


    caption.setCharacterSize(15);
    caption.setPosition(565,330);
    caption.setColor(sf::Color::Black);

    txtPoint.setString(point);
    caption.setString("Guess Your Point : ");

    while (running){
        while (App.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                return cardgame::datas::currentRunningWindow;
            if (event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::Escape)
                    return cardgame::MAINMENUSCREEN;

                if (event.key.code >= sf::Keyboard::Num0 and event.key.code <= sf::Keyboard::Num9){
                    point += static_cast<char>(event.key.code + 22);
                }
                if (event.key.code == sf::Keyboard::BackSpace)
                    point.erase(point.length() - 1);
                if (event.key.code == sf::Keyboard::Return){
                    if (point.length() > 0){
                        point >> cardgame::datas::guessedPoint;
                    return cardgame::datas::currentRunningWindow;
                    }
                }
            }
        }
    App.draw(mainR);
    App.draw(Titlebar);
    App.draw(caption);
    App.draw(txtPoint);
    App.display();
    }
return -1;
}

#endif // GUESSPOINT_H
