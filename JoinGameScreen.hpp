#ifndef JOINGAMESCREEN_H
#define JOINGAMESCREEN_H
#include <iostream>
#include <cstring>
#include <string>

#include "Screen.hpp"
#include "Exception.hpp"
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include "datas.hpp"

class JoinGameScreen : public cardgame::Screen{
private:
   // sf::TcpSocket socket;
    std::string connectNumber;
public:
    JoinGameScreen (void);
    virtual int Run (sf::RenderWindow &App);
};

JoinGameScreen :: JoinGameScreen (void) {

}

int JoinGameScreen :: Run (sf::RenderWindow &App){
    bool Running = true;
    bool askName = true;

    std::size_t received;
    char *uname = new char[64];
    sf::IpAddress ip;
    sf::Event event;
    sf::RectangleShape mainRect;
    sf::RectangleShape titlebar;
    sf::Font font;
    if(!font.loadFromFile("verdanab.ttf"))
        throw cardgame::Exception::FILE_CANNOT_LOAD;

    /// this indicates that this game will played as client
    cardgame::datas::iAmServer = false;

    mainRect.setSize(sf::Vector2f(400,150));
    //mainRect.setFillColor(sf::Color::Green);
    mainRect.setFillColor(sf::Color(0,255,0,100));
    titlebar.setFillColor(sf::Color::Green);
    mainRect.setOutlineThickness(2);
    mainRect.setOutlineColor(sf::Color::Black);
    titlebar.setOutlineThickness(2);
    titlebar.setOutlineColor(sf::Color::Black);
    titlebar.setSize(sf::Vector2f(400,30));
    mainRect.setPosition(481, 306);
    titlebar.setPosition(481, 306);
    sf::Text textTitle;
    textTitle.setPosition(485,311);
    textTitle.setCharacterSize(21);
    textTitle.setFont(font);
    textTitle.setColor(sf::Color::Blue);
    textTitle.setString("Ip/Computer Name to Connect.");

    sf::Text number;
    number.setFont(font);
    number.setPosition (485, 363);
    number.setCharacterSize (21);
    number.setColor(sf::Color::Blue);
    number.setString(connectNumber);
    //connectNumber = "127.0.0.1";

    while (Running){
        if (askName)
            textTitle.setString("Enter Your Name.");
        else
            textTitle.setString("Enter Computer IP to connect.");

        while (App.pollEvent(event)){
            if (event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::Escape)
                    return 0;
                else if (event.key.code == sf::Keyboard::Return){
                    if (askName){
                        cardgame::datas::playerName[0] = connectNumber;
                        connectNumber = "127.0.0.1";
                        askName = false;
                        continue;
                    }else
                        ip = connectNumber;
                    std::cout << "ip : " << ip << std::endl;

                    /** socket[0] from namespace datas is used for clients to conenct with server and all four socket is used bu server
                    to connect with clients **/
                    if (!cardgame::datas::socket[0].connect(ip,cardgame::datas::PORT) == sf::Socket::Done){
                        number.setString("Cannot Connect to " + ip.toString());
                        number.setPosition(485, 400);
                        App.draw(number);
                        App.display();
                        sf::sleep(sf::milliseconds(100));
                        throw cardgame::Exception(cardgame::Exception::CANNOT_CONNECT_TO_SERVER,ip.toString());
                    }

                    strcpy (uname, cardgame::datas::playerName[0].c_str());

                    cardgame::datas::socket[0].send(uname, static_cast<std::size_t>(cardgame::datas::playerName[0].length() + 1));
                    cardgame::datas::socket[0].receive(&cardgame::datas::myId,sizeof(int), received);

                    connectNumber = "Connected to : " + ip.toString() ;
                    std::cout << "My id : " << cardgame::datas::myId << std::endl;
                    number.setString("Connected successfully...");
                    cardgame::datas::iAmServer = false;
                    number.setPosition(485, 400);
                    App.draw(number);
                    App.display();
                    sf::sleep(sf::seconds(1));

                    return cardgame::GAMESCREEN;
                    /// connection process here
                }
                else if ((event.key.code >= sf::Keyboard::Num0 and event.key.code <= sf::Keyboard::Num9)
                        or event.key.code == sf::Keyboard::Period
                        or (askName and event.key.code >= sf::Keyboard::A and event.key.code <= sf::Keyboard::Z)){
                    if (event.key.code >= sf::Keyboard::Num0 and event.key.code <= sf::Keyboard::Num9)
                        connectNumber += static_cast<char>(event.key.code + 22);
                    else if (event.key.code >= sf::Keyboard::A and event.key.code <= sf::Keyboard::Z)
                        connectNumber += static_cast<char>(event.key.code + 65);
                    else
                        connectNumber += static_cast<char> (event.key.code - 4);
                }else if (event.key.code == sf::Keyboard::BackSpace){
                    if (connectNumber.length() > 0)
                        connectNumber.erase(connectNumber.length() - 1);
                }
            }
    }

    number.setString(connectNumber);
    App.draw(mainRect);
    App.draw(titlebar);
    App.draw(textTitle);
    App.draw(number);
   // std::cout << "Number : " <<  connectNumber << std::endl;
    App.display();
    }
return cardgame::EXIT;
}
#endif // JOINGAMESCREEN_H
