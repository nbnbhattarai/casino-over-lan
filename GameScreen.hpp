#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <cstdlib>
#include <ctime>
#include <thread>
#include <X11/Xlib.h>

#include "card.hpp"
#include "Screen.hpp"
#include "Exception.hpp"
#include "datas.hpp"
#include "ServerSide.hpp"
#include "ClientSide.hpp"

//#include "card.hpp"

class GameScreen : public cardgame::Screen{
private:
    bool threadRunning;
    std::thread threadSC;
    std::thread thRender;
    /// this holds all cards of 4 players if this is server otherwise holds only one set
    cardgame::Card *cardpack;
    bool exitCommand;
public:
    GameScreen (void);
    void render (sf::RenderWindow &App);
    virtual int Run (sf::RenderWindow &App);
};

GameScreen :: GameScreen (void)
:threadRunning(true), exitCommand(false){


}

void GameScreen::render (sf::RenderWindow &App){
    bool Running = true;
    sf::Event event;
    sf::Font font;
    sf::Text TxtMsg;

    XInitThreads();

    cardgame::datas::allCard[0].setPosition(80, 600);
    sf::Vector2i mpos;

    if(!font.loadFromFile("verdanab.ttf"))
        throw cardgame::Exception(cardgame::Exception::FILE_CANNOT_LOAD,"verdanab.ttf");

    TxtMsg.setFont(font);
    TxtMsg.setString("Game Starts After Connecting All Players");
    TxtMsg.setCharacterSize(30);
    TxtMsg.setPosition(600,369);

    while (Running){
          //  std::cout << "this is game screen" << std::endl;
        while (App.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                exitCommand = true;
                return;
            }
            if (event.type == sf::Event::KeyPressed){
                switch (event.key.code){
                case sf::Keyboard::Escape:
                    cardgame::datas::currentRunningWindow = cardgame::GAMESCREEN;
                    exitCommand = true;
                    return;
                break;
                default:
                    break;
                }
            }
            mpos = sf::Mouse::getPosition();
            cardgame::datas::allCard[0].mouseOverEvent (static_cast<sf::Vector2f>(mpos));
            if (event.type == sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                cardgame::datas::allCard[0].mouseClickEvent (static_cast<sf::Vector2f>(mpos));
            }
        }

        App.clear(sf::Color::Red);
        cardgame::datas::allCard[0].draw(App);
        App.display();
        /// here game playing event takes place
    }
exitCommand = true;
}

int GameScreen::Run(sf::RenderWindow &App){
    sf::Font font;
    sf::Text TxtMsg;

    XInitThreads();

    cardgame::datas::allCard[0].setPosition(80, 600);
    sf::Vector2i mpos;

    char *gameStart = new char;
    std::size_t received;


    if(!font.loadFromFile("verdanab.ttf"))
        throw cardgame::Exception(cardgame::Exception::FILE_CANNOT_LOAD,"verdanab.ttf");

    TxtMsg.setFont(font);
    TxtMsg.setString("Game Starts After Connecting All Players");
    TxtMsg.setCharacterSize(30);
    TxtMsg.setPosition(600,369);

    if (cardgame::datas::iAmServer){
        std::cout << "Here Server thread is created." << std::endl;
        threadSC = std::thread (cardgame::Server);
        /// server's and client's thread is detached from  this function's thread
        threadSC.detach ();
    }else{
        App.clear ();
        App.draw (TxtMsg);
        App.display ();

        std::cout << "gameStart identification is going to receive." << std::endl;
        cardgame::datas::socket[0].receive(gameStart,sizeof(char),received);
        if (*gameStart == 'n'){
            TxtMsg.setString("Game exited by server.");
            sf::sleep(sf::milliseconds(500));
            return cardgame::MAINMENUSCREEN;
        }
        App.clear ();
        std::cout << "All players are connected , game starts now." << std::endl;
        TxtMsg.setString("All Players Connected, Game Starts Now.");
        App.draw (TxtMsg);
        App.display ();
        std::cout << "Here Client thread is created." << std::endl;
        threadSC = std::thread (cardgame::Client);
        /// client's thread is detached from  this function's thread
        threadSC.detach ();
    }

    std::cout << "Here game window starts to run" << std::endl;
    thRender = std::thread (&GameScreen::render,this,std::ref(App));

    /// THIS IS NOW SHIFTED TO SEPERATE THREAD RENDER
    /*while (Running){
          //  std::cout << "this is game screen" << std::endl;
        while (App.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                return cardgame::EXITCONFIRMSCREEN;
            }
            if (event.type == sf::Event::KeyPressed){
                switch (event.key.code){
                case sf::Keyboard::Escape:
                    cardgame::datas::currentRunningWindow = cardgame::GAMESCREEN;
                    return cardgame::EXITCONFIRMSCREEN;
                break;
                default:
                    break;
                }
            }
            mpos = sf::Mouse::getPosition();
            cardgame::datas::allCard[0].mouseOverEvent (static_cast<sf::Vector2f>(mpos));
            if (event.type == sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                cardgame::datas::allCard[0].mouseClickEvent (static_cast<sf::Vector2f>(mpos));
            }
        }

        App.clear(sf::Color::Red);
        cardgame::datas::allCard[0].draw(App);
        App.display();
        /// here game playing event takes place
    }
    */

    while (!exitCommand)
        ;
return cardgame::MAINMENUSCREEN;
}
#endif // GAMESCREEN_H
