#ifndef HELPANDABOUTSCREEN_H
#define HELPANDABOUTSCREEN_H
#include "Screen.hpp"
#include "Exception.hpp"
#include <iostream>
#include <fstream>

class HelpAndAboutScreen : public cardgame::Screen {
private:
    std::ifstream inFile;
    std::string helpText;
public:
    HelpAndAboutScreen (void);
    virtual int Run (sf::RenderWindow &App);
};

HelpAndAboutScreen :: HelpAndAboutScreen (void) {
    char ch;
    inFile.open ("helptext");
    if (!inFile)
        throw cardgame::Exception::FILE_CANNOT_LOAD;
    while (inFile){
        inFile >> ch;
        helpText += ch;
    }
}
int HelpAndAboutScreen :: Run (sf::RenderWindow &App){
    sf::RectangleShape mainrect;
    mainrect.setSize(sf::Vector2f(1000,720));
    mainrect.setPosition(183, 24);
    mainrect.setOutlineThickness(4);
    mainrect.setOutlineColor(sf::Color::Blue);
    mainrect.setFillColor(sf::Color::Black);
    sf::Text txtTitle;
    sf::Text txtHelp;
    sf::Font font;
    if(!font.loadFromFile("verdanab.ttf"))
        throw cardgame::Exception::FILE_CANNOT_LOAD;

    txtTitle.setFont(font);
    txtTitle.setString("Help");
    txtTitle.setCharacterSize(25);
    txtTitle.setPosition(633,25);
    txtTitle.setColor(sf::Color::White);

    txtHelp.setFont(font);
    txtHelp.setString(helpText);
    txtHelp.setCharacterSize(12);
    txtHelp.setColor(sf::Color::Green);
    txtHelp.setPosition(187, 55);

    sf::Event event;

    bool Running = true;
    while (Running){
        while (App.pollEvent(event)){
            if (event.type == sf::Event::KeyPressed
                and event.key.code == sf::Keyboard::Escape
                )
                    return 0;
    }
    App.clear();
    App.draw(mainrect);
    App.draw(txtTitle);
    App.draw(txtHelp);
    App.display();
    }
return -1;
}
#endif // HELPANDABOUTSCREEN_H
