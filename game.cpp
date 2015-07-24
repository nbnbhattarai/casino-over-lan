#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include <thread>


namespace CardGame{
    int optionSelected;

    //void printHelpAndAbout(sf::RenderWindow &);
    class MainMenu{
    private:
        int opt;
        sf::Vector2i mpos;
        sf::Texture menuNormal;
        sf::Texture menuMouseClicked[5];
        sf::Texture menuMouseover[5];
        sf::Sprite menuShow;
        sf::Texture menuBackground;
        sf::Sprite background;
        int lx, ly;
        float scalex, scaley; 
        float unitx, unity;

    public:
        MainMenu(int x, int y)
        :lx(x), ly(y), scalex (0.8), scaley (0.8){
            int height, width;
            scalex = 0.8;
            scaley = 0.8;

            menuBackground.loadFromFile("card_back2.jpg");
            background.setTexture(menuBackground);
            background.setScale(0.711,0.711);

            const std::string names[] = {"startgame","joingame","highscore","help","exit"};
            menuNormal.loadFromFile("Pictures/menu_init.png");
            for(int i = 0; i < 5; i++){
                menuMouseover[i].loadFromFile("Pictures/menu_"+names[i]+"_mouseover.png");
            }
            for(int i = 0; i < 5; i++){
                menuMouseClicked[i].loadFromFile("Pictures/menu_"+names[i]+"_mouseclicked.png");
            }

            height = menuMouseClicked[0].getSize().y; // * scaley;
            width = menuMouseClicked[0].getSize().x; // * scalex;

            menuShow.setPosition(683-(width/2),0);

            unitx = static_cast<float>(height) / 76.0;
            unity = static_cast<float>(width) / 100.0;

            std::cout << "unitx : " << unitx << " and unity : " << unity << std::endl;
            menuShow.setTexture(menuNormal);
        }

        int run(sf::RenderWindow &gameWindow){
            int cy = 7;
            while(gameWindow.isOpen()){
                sf::Event event;
                while(gameWindow.pollEvent(event)){
                    if(event.type == sf::Event::Closed
                       or event.type == sf::Keyboard::isKeyPressed(sf::Keyboard::Q)
                       or event.type == sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)
                        ){
                        gameWindow.close();
                    }

                    /// this event for mouse button clicked
                    if (event.type == sf :: Event :: MouseButtonPressed
                        and event.mouseButton.button == sf :: Mouse :: Left
                        ){
                        mpos = sf::Mouse::getPosition();
                        if((mpos.x > lx + unitx * 14 and mpos.x < lx + unitx * 86) and
                            (mpos.y > ly + unity * cy  and mpos.y < ly + unity * 56)){
                            /// this is inside of menus
                            opt = static_cast<int>(mpos.y - (cy * unity)) / static_cast<int>(cy  * unity);
                            if(opt <= 4){
                                menuShow.setTexture(menuMouseover[opt]);
                                switch ( opt ){
                                    case 0:
                                        std::cout << "New game clicked " << std::endl;
                                        break;

                                    case 1:
                                        std::cout << "Join game clicked " << std::endl;
                                        break;

                                    case 2:
                                        std::cout << "High Scores clicked " << std::endl;
                                        break;

                                    case 3:
                                        std::cout << "Help and about clicked " << std::endl;
                                        //gameWindow.close ();
//                                        printHelpAndAbout(gameWindow);
                                        break;
                                    case 4:
                                        std::cout << "Exit game clicked " << std::endl;
                                        //gameWindow.close();
                                        break;
                                }
                            return opt;
                            }else
                                menuShow.setTexture(menuNormal);
                            }else{
                                menuShow.setTexture(menuNormal);
                            }
                    }else{
                        mpos = sf::Mouse::getPosition();
                        if((mpos.x > lx + unitx * 14 and mpos.x < lx + unitx * 86) and
                            (mpos.y > ly + unity * cy  and mpos.y < ly + unity * 56)){
                            /// this is inside of menus
                            opt = static_cast<int>(mpos.y - (cy * unity)) / static_cast<int>(cy  * unity);
                            if(opt <= 4){
                                menuShow.setTexture(menuMouseover[opt]);

                            }else
                                menuShow.setTexture(menuNormal);
                            }else{
                                menuShow.setTexture(menuNormal);
                            }
                        }if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)
                            or sf::Keyboard::isKeyPressed(sf::Keyboard::Q)
                           ){
                            gameWindow.close();
                            }
                    menuShow.setPosition(lx,ly);
                    menuShow.setScale(scalex,scaley);
                    gameWindow.clear(sf::Color::Black);
                    gameWindow.draw(background);
                    gameWindow.draw(menuShow);
                    gameWindow.display();


                }
            }
        return -1;
        }
        };
    class HelpAboutWindow{
    private:
        sf::Texture txHelp;
        sf::Sprite spHelp;
    public:
        HelpAboutWindow(){
            txHelp.loadFromFile("Pictures/card_back1.jpg");
            spHelp.setTexture(txHelp);
        }
        int run(sf::RenderWindow &gameWindow){
            while (gameWindow.isOpen()){
                sf::Event event;
                while(gameWindow.pollEvent(event)){
                    if(event.type == sf::Event::Closed
                        or event.type == sf::Keyboard::isKeyPressed(sf::Keyboard::Q)
                        or event.type == sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)
                        ){
                            std::cout << "help and about close" << std::endl;
                            return -1;
                    }
                }
                gameWindow.clear();
                gameWindow.draw(spHelp);
                gameWindow.display();
            }
        }
    };


    class Game{
    private:

    public:
        Game (std::string playerName){}
        void mainMenu ();
    };
}

int main(void){
    sf::RenderWindow gameWindow (sf::VideoMode(1366,768),"LAN Casino");
    int valueReturn;
    CardGame :: MainMenu m(200,0);
    CardGame :: optionSelected = m.run (gameWindow);
    CardGame :: HelpAboutWindow habout;
    valueReturn = habout.run(gameWindow);
    if (valueReturn == -1)
        gameWindow.close();
    return 0;
}

