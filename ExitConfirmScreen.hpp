#ifndef EXITCONFIRMSCREEN_H
#define EXITCONFIRMSCREEN_H
#include "Screen.hpp"
#include <SFML/Graphics.hpp>
#include "datas.hpp"

class ExitConfirmScreen : public cardgame::Screen {
private:
    int height, width;
public:
    ExitConfirmScreen ();
    virtual int Run (sf::RenderWindow &App);
};

ExitConfirmScreen :: ExitConfirmScreen ()
:height(150), width(400){

}

int ExitConfirmScreen :: Run (sf::RenderWindow &App){
    bool Running = true;
    sf::Event event;
    sf::Vector2f mpos;
    sf::Text askText, yesText, noText;
    sf::Font font;
    if(!font.loadFromFile("verdanab.ttf"))
        throw cardgame::Exception(cardgame::Exception::FILE_CANNOT_LOAD,"verdanab.ttf");

    askText.setFont(font);
    askText.setCharacterSize(21);
    askText.setColor(sf::Color::Black);
    askText.setString("Do you want to Exit ?");

    yesText.setFont(font);
    yesText.setCharacterSize(15);
    yesText.setColor(sf::Color::Black);
    yesText.setString("YES");


    noText.setFont(font);
    noText.setCharacterSize(15);
    noText.setColor(sf::Color::Black);
    noText.setString("NO");

    sf::RectangleShape mainR, yesButton, noButton;

    mainR.setSize(sf::Vector2f(width,height));
    mainR.setFillColor(sf::Color::Green);
    mainR.setOutlineColor(sf::Color::Black);
    mainR.setOutlineThickness(2);
    mainR.setPosition(sf::Vector2f((683-(width/2)),(307-(height/2))));

    yesButton.setSize (sf::Vector2f(80,30));
    yesButton.setFillColor (sf::Color::Green);
    yesButton.setOutlineColor (sf::Color::Black);
    yesButton.setOutlineThickness (1);
    yesButton.setPosition ((683 + width/2 - 90*2),(307+(height/2) - 35));

    noButton.setSize (sf::Vector2f(80,30));
    noButton.setFillColor (sf::Color::Green);
    noButton.setOutlineColor (sf::Color::Black);
    noButton.setOutlineThickness (1);
    noButton.setPosition ((683 + width/2 - 90),(307+(height/2) - 35));

    askText.setPosition((683-(width/2)) + 35,(307-(height/2) + 30));
    yesText.setPosition ((683 + width/2 - 90*2 + 8),(307+(height/2) - 35 + 4));
    noText.setPosition ((683 + width/2 - 90 + 19),(307+(height/2) - 35 + 4));

    while (Running){
        mpos = static_cast<sf::Vector2f>(sf::Mouse::getPosition());
        while (App.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                return -1;
            if(event.type == sf::Event::KeyPressed){
                switch (event.key.code){
                case sf::Keyboard::Escape:
                    return 0;
                break;
                case sf::Keyboard::Y:
                    return cardgame::EXIT;
                    break;
                case sf::Keyboard::N:
                    return cardgame::datas::currentRunningWindow;
                    break;
                default:
                    return 0;
                    break;
                }
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                sf::sleep(sf::milliseconds(10));
                if (yesButton.getGlobalBounds().contains (mpos)){
                    yesButton.setFillColor (sf::Color::Magenta);
                    sf::sleep(sf::microseconds(200));
                    return cardgame::EXIT;
                }
                if (noButton.getGlobalBounds ().contains (mpos)){
                    noButton.setFillColor (sf::Color::Magenta);
                    sf::sleep(sf::microseconds(200));
                    return cardgame::datas::currentRunningWindow;
                }
            }

            if (yesButton.getGlobalBounds().contains (mpos)
                or yesText.getGlobalBounds().contains (mpos))
                yesButton.setFillColor (sf::Color::Blue);
            else
                yesButton.setFillColor (sf::Color::Green);

            if (noButton.getGlobalBounds ().contains (mpos))
                noButton.setFillColor (sf::Color::Blue);
            else
                noButton.setFillColor (sf::Color::Green);

        }
        App.draw(mainR);
        App.draw(yesButton);
        App.draw(noButton);
        App.draw(askText);
        App.draw(yesText);
        App.draw(noText);
        App.display();
    }
return -1;
}
#endif // EXITCONFIRMSCREEN_H
