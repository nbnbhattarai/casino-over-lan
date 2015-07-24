#ifndef NEWGAMESCREEN_H
#define NEWGAMESCREEN_H
#include <iostream>
#include <thread>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Screen.hpp"
#include "datas.hpp"

class NewGameScreen : public cardgame::Screen{
private:
    std::string playerName;
    sf::TcpListener listener;
    //sf::TcpSocket *socket;
    int nPlayer;
    std::thread *joinThread;
    bool joinedAllPlayers;

public:
    NewGameScreen(void);
    virtual int Run(sf::RenderWindow &App);
    void joinPlayers();
};

NewGameScreen :: NewGameScreen (void)
:nPlayer (1), joinedAllPlayers (false){
    //socket = new sf::TcpSocket[4];
}

int NewGameScreen :: Run (sf::RenderWindow &App){

    sf::RectangleShape mainR;
    sf::RectangleShape titlebar;
    sf::Texture t_background;
    sf::Sprite background;

    char *gameStart = new char;
    *gameStart = 's';

    int lvl = 1;

    if(!t_background.loadFromFile("Pictures/card_back1.jpg"))
        throw cardgame::Exception(cardgame::Exception(cardgame::Exception::FILE_CANNOT_LOAD, "Pictures/card_back1.jpg"));

    background.setTexture(t_background);
    background.setScale(0.7,0.7);

    sf::Event event;

    bool Running = true;
    bool gettingname = true;

    sf::Text txtCaption;
    sf::Text txtPlayerName;
    sf::Text txtPlayerNames[4];
    sf::Font font;

    font.loadFromFile("verdanab.ttf");

    txtCaption.setFont(font);
    txtCaption.setPosition(461,87);
    txtCaption.setCharacterSize(24);
    txtCaption.setColor(sf::Color::Black);

    txtPlayerName.setFont(font);
    txtPlayerName.setPosition(461,115);
    txtPlayerName.setCharacterSize(21);
    txtPlayerName.setColor(sf::Color::Black);

    for (int i = 0; i < 4; ++i){
        txtPlayerNames[i].setFont(font);
        txtPlayerNames[i].setPosition(461,120 + i * 35);
        txtPlayerNames[i].setCharacterSize(21);
        if (i == 0)
            txtPlayerNames[i].setColor(sf::Color::Red);
        else
            txtPlayerNames[i].setColor(sf::Color::Black);
        txtPlayerNames[i].setString(cardgame::datas::playerName[i]);
    }

    mainR.setSize(sf::Vector2f(450,600));
    mainR.setPosition(456,82);
    mainR.setFillColor(sf::Color::Green);
    mainR.setOutlineThickness(2);
    mainR.setOutlineColor(sf::Color::Black);
    mainR.setFillColor(sf::Color(0,255,0,100));

    titlebar.setSize(sf::Vector2f(450,35));
    titlebar.setPosition(456,82);
    titlebar.setFillColor(sf::Color::Green);
    titlebar.setOutlineThickness(2);
    titlebar.setOutlineColor(sf::Color::Black);
    mainR.setFillColor(sf::Color(0,255,0,100));

    int i = 0;
    while (Running){
        (i < 300 ? i++ : i = 0);
        while (App.pollEvent(event)){
                if (lvl < 1200) lvl++;
                else lvl = 0;

                if (gettingname)
                    txtCaption.setString("Enter Your Name: ");
                else{
                    if (lvl % 1200 == 0)
                        txtCaption.setString("Waiting for connection...");
                    else if (lvl%800 == 0)
                        txtCaption.setString("Waiting for connection..");
                    else if (lvl%400 == 0){
                        txtCaption.setString("Waiting for connection...");
                        lvl = 3;
                    }
                }
            if(event.type == sf::Event::KeyPressed){
                if(event.key.code >= 0 and event.key.code <= 25
                   and gettingname
                   ){
                    playerName += static_cast<char>(event.key.code + 65);
                }else if (event.key.code == sf::Keyboard::BackSpace and playerName.length() > 0){
                    playerName.erase(playerName.length() - 1);
                }
                if(event.key.code == sf::Keyboard::Return){
                    gettingname = false;
                    joinThread = new std::thread ([this]{joinPlayers();});
                    joinThread->detach ();

                    /// this is to disappear user's name slightly
                    for (int i = 256; i > 0; i-=5 ){
                        cardgame::datas::playerName[0] = playerName;
                        txtCaption.setString("Waiting for connection.");
                        sf::sleep(sf::milliseconds(3));
                        txtPlayerName.setColor(sf::Color(256-i,0,0,200));
                        App.clear();
                        App.draw(background);
                        App.draw(mainR);
                        App.draw (titlebar);
                        App.draw(txtPlayerName);
                        App.draw(txtCaption);

                        for (int i = 0; i < nPlayer; i++){
                            txtPlayerNames[i].setString(cardgame::datas::playerName[i+1]);
                            App.draw (txtPlayerNames[i+1]);
                        }

                        App.display();
                    }
                }
                if (event.key.code == sf::Keyboard::Escape){
                    joinedAllPlayers = true;
                    sf::sleep(sf::milliseconds(100));
                    return cardgame::MAINMENUSCREEN;
                }
            }


        }

        /// After all the three player are connected to server
        if (nPlayer == 4){
                txtCaption.setString("All Players Connected.");
                App.clear();
                App.draw(background);
                App.draw(mainR);
                App.draw (titlebar);
                App.draw(txtPlayerName);
                App.draw(txtCaption);

                for (int i = 0; i < nPlayer; i++){
                    txtPlayerNames[i].setString(cardgame::datas::playerName[i]);
                    App.draw (txtPlayerNames[i]);
                }

                App.display();
                sf::sleep (sf::seconds(2));

                cardgame::datas::iAmServer = true;

                return cardgame::GAMESCREEN;
            }

        txtPlayerName.setString(playerName);

        App.clear();
        App.draw(background);
        App.draw(mainR);
        App.draw (titlebar);
        App.draw(txtPlayerName);
        App.draw(txtCaption);
        for (int i = 0; i < nPlayer; i++){
            txtPlayerNames[i].setString(cardgame::datas::playerName[i]);
            App.draw (txtPlayerNames[i]);
        }
        App.display();
    }
return cardgame::EXIT;
}

void NewGameScreen :: joinPlayers (){
    joinedAllPlayers = false;
    char *gameStart = new char;
    char *uname = new char[64];
    std::size_t size_r;
    if (!listener.listen(cardgame::datas::PORT) == sf::Socket::Done){
        throw cardgame::Exception(cardgame::Exception::CANNOT_BIND_TO_PORT);
    }
    while (!joinedAllPlayers and nPlayer < 4){
        if (listener.accept(cardgame::datas::socket[nPlayer]) != sf::Socket::Done){
            throw cardgame::Exception(cardgame::Exception::CANNOT_ACCEPT_CONNECTION);
        }
        std::cout << "Connection received of " << cardgame::datas::socket[nPlayer].getRemoteAddress() << std::endl;
        cardgame::datas::socket[nPlayer].receive(uname, 64,size_r);
        cardgame::datas::socket[nPlayer].send(&nPlayer,sizeof(int));
        cardgame::datas::playerName[nPlayer] = uname;
        std::cout << " name : " << cardgame::datas::playerName[nPlayer] << std::endl;
        nPlayer++;
    }
    if (nPlayer == 4)
        joinedAllPlayers = true;
    listener.close();
    std::cout << "tcp listener closed \nAnd verification char "<< (nPlayer==4?'y':'n') << "is sending to all players" << std::endl;

    if (nPlayer == 4)
        *gameStart = 'y';
    else
        *gameStart = 'n';

    for (int i = 1; i < 4; ++i){
        cardgame::datas::socket[i].send(gameStart,sizeof(char));
    }
    std::cout << "verification char is sent to all clients" << std::endl;
}

#endif // NEWGAMESCREEN_H
