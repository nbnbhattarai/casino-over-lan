#include "Screens.hpp"
#include <cstdlib>
#include <ctime>
#include <thread>
#include <X11/Xlib.h>

int main(void)
{
    if (XInitThreads() == 0){
        std::cout << "multiple thread can not run in this system" << std::endl;
        return -1;
    }

    GameScreen gameScreen;
    MenuScreen menuScreen;
    NewGameScreen newGameScreen;
    HelpAndAboutScreen helpAndAboutScreen;
    JoinGameScreen joinGameScreen;
    HighScoreScreen highScoreScreen;
    ExitConfirmScreen exitConfirmScreen;
    sf::RenderWindow gameWindow (sf::VideoMode(1366,768), "Lan Casino", sf::Style::Fullscreen);
    int screenId = 0;
    std::vector<cardgame::Screen*>screens;

    /*
    if (!XInitThreads()){
        std::cout << "This system doesnot support multithreading, This App cannot run." << std::endl;
        return -1;
    }
    */

    srand(time(NULL));
    screens.push_back(&menuScreen);
    screens.push_back(&newGameScreen);
    screens.push_back(&joinGameScreen);
    screens.push_back(&highScoreScreen);
    screens.push_back(&helpAndAboutScreen);
    screens.push_back(&exitConfirmScreen);
    screens.push_back(&gameScreen);

    try{
        while (screenId >= 0){
            screenId = screens[screenId]->Run (gameWindow);
        }
    }catch (cardgame::Exception exc){
        gameWindow.close();
        exc.display ();
    }
    return 0;
}

