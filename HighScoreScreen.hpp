#ifndef HIGHSCORESCREEN_H
#define HIGHSCORESCREEN_H

#include <fstream>
#include "Screen.hpp"
#include "ExitConfirmScreen.hpp"
#include "Exception.hpp"

class HighScoreScreen : public cardgame::Screen {
private:
    std::string fileName;
public:
    HighScoreScreen ();
    virtual int Run (sf::RenderWindow &App);
};

HighScoreScreen :: HighScoreScreen ()
:fileName ("HighScore")
{

}

int HighScoreScreen :: Run (sf::RenderWindow &App){
    bool Running = true;
    sf::Event event;
    std::ifstream inFile;
    inFile.open (fileName);
    if (!inFile)
        throw cardgame::Exception(cardgame::Exception::FILE_CANNOT_LOAD,fileName);

    while (Running){
        while (App.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                return -1;
            if (event.type == sf::Event::KeyPressed){

            }
        }
    App.clear();
    App.display();
    }
return -1;
}

#endif // HIGHSCORESCREEN_H
