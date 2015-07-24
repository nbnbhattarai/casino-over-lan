#ifndef MENUSCREEN_H
#define MENUSCREEN_H
#include <iostream>
#include "Screen.hpp"
#include "Exception.hpp"
#include "ExitConfirmScreen.hpp"

class MenuScreen : public cardgame::Screen {
private:
    int lx, ly;
    sf::Texture menuNormal;
    sf::Texture menuMouseClicked[5];
    sf::Texture menuMouseover[5];
    sf::Texture menuBackground;

    sf::Sprite menuShow;
    sf::Sprite background;
    bool isPlaying;

    ExitConfirmScreen exitConfirmScreen;

    float unitx, unity;
public:
    MenuScreen (void);
    virtual int Run (sf::RenderWindow &App);
};

MenuScreen :: MenuScreen (void){
    int height, width;

    lx = 200;
    ly = 0;
    isPlaying = false;


    menuBackground.loadFromFile("Pictures/card_back2.jpg");
    background.setTexture(menuBackground);
    background.setScale(0.711,0.711);

    const std::string names[] = {"startgame","joingame","highscore","help","exit"};
    menuNormal.loadFromFile("Pictures/menu_init.png");
    for(int i = 0; i < 5; i++){
        if(!menuMouseover[i].loadFromFile("Pictures/menu_"+names[i]+"_mouseover.png")){
            throw cardgame::Exception::FILE_CANNOT_LOAD;
        }
    }

    for(int i = 0; i < 5; i++){
        if(!menuMouseClicked[i].loadFromFile("Pictures/menu_"+names[i]+"_mouseclicked.png")){
            throw cardgame::Exception::FILE_CANNOT_LOAD;
        }
    }
    height = menuNormal.getSize().y;
    width = menuNormal.getSize().x;

    menuShow.setScale(0.8,0.8);
    menuShow.setPosition(lx, ly);

    /// these pixel per unit
    unitx = static_cast<float>(height) / 76;
    unity = static_cast<float>(width) / 100;
    std::cout << "unitx = " << unitx << "and unity = " << unity << std::endl;

    /// initially set texture (image) of menu to normal
    menuShow.setTexture(menuNormal);
}


int MenuScreen :: Run(sf::RenderWindow &App){

    /// App is running
    bool running = true;
    sf::Vector2i mpos;
    int opt;

    /// this integer is height of individual option portion
    int cy = 7;
    sf::Event event;
    while(running){
        while (App.pollEvent (event)){
            if(event.type == sf::Event::Closed)
                return -1;
            if(event.type == sf::Event::KeyPressed){
                switch (event.key.code){
                case sf::Keyboard::Escape:
                    cardgame::datas::currentRunningWindow = cardgame::MAINMENUSCREEN;
                    return cardgame::EXITCONFIRMSCREEN;
                    break;
                default:
                    break;
                }
            }
        mpos = sf::Mouse::getPosition();
        opt = static_cast<int>(mpos.y - (cy * unity)) / static_cast<int>(cy  * unity);
        if((mpos.x > (lx + unitx * 14) and mpos.x < (lx + unitx * 86))
            and (mpos.y > (ly + unity * cy)  and mpos.y < (ly + unity * 56))
            ){
            if(event.type == sf::Event::MouseButtonPressed
               and event.mouseButton.button == sf::Mouse::Left
               ){
                    if (opt <= 4){
                        menuShow.setTexture(menuMouseClicked[opt]);
                        App.clear();
                        App.draw(background);
                        App.draw(menuShow);
                        App.display();
                        sf::sleep(sf::milliseconds(100));
                        if (opt == 4){
                            if (exitConfirmScreen.Run(App) == -1)
                                return -1;
                        }
                        else
                            return opt + 1;
                    }
                }else{
                    if(opt <= 4)
                        menuShow.setTexture(menuMouseover[opt]);
                    else
                        menuShow.setTexture(menuNormal);
                }
            }
        }
        App.clear();
        App.draw(background);
        App.draw(menuShow);
        App.display();
    }
    return -1;
}
#endif // MENUSCREEN_H
