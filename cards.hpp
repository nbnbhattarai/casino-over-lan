#ifndef CARDS_H
#define CARDS_H

#include "card.hpp"
#include <SFML/Window.hpp>
namespace cardgame{
class Cards {
private:
    cardgame::Card *cards;
    unsigned int nCards;
    bool *notShown;
    bool showing;
    int lx, ly;
public:
    Cards (unsigned int num = 13, int x = 0, int y = 0);
    void setPosition (int x, int y);
    void draw (sf::RenderWindow &App);
    void show (bool tf);

    void mouseClickEvent (sf::Vector2f pos);
    void mouseOverEvent (sf::Vector2f pos);

    void setDetail (int sn, cardgame::CardValue cv, cardgame::CardType ct);
    cardgame::Card& operator [] (const int index);
};

Cards :: Cards (unsigned int num, int x, int y)
:nCards (num),showing (false), lx (x), ly (y){
    cards = new cardgame::Card[nCards];
    notShown = new bool [nCards];
    for (unsigned int i = 0; i < nCards; i++)
        notShown[i] = true;
}

void Cards :: setPosition(int x, int y){
    lx = x;
    ly = y;
}

void Cards :: show  (bool tf)
{
    showing = tf;
}

void Cards :: setDetail(int sn, cardgame::CardValue cv, cardgame::CardType ct){
    cards[sn].setType(ct);
    cards[sn].setValue(cv);
    cards[sn].initPicture();
}

cardgame::Card& Cards :: operator [] (const int index)
{
    return cards[index];
}

void Cards::mouseOverEvent(sf::Vector2f pos){
    for (unsigned int i = 0; i < nCards; ++i){
        if (cards[i].getGlobalBounds().contains(pos)){
            cards[i].setOutlineColor(sf::Color::Blue);
            cards[i].setOutlineThickness(2);
        }
        cards[i].setOutlineThickness(0);
    }
}

void Cards::mouseClickEvent(sf::Vector2f pos){
    for (unsigned int i = 0; i < nCards; ++i){
        if (cards[i].getGlobalBounds().contains(pos)){
            for (int i = 0; i < 50; ++i){
                sf::sleep(sf::milliseconds(10));
                cards[i].setPosition(cards[i].getPosition().x, cards[i].getPosition().y - 1);
            }
            notShown[i] = false;
        }
    }
}

void Cards::draw(sf::RenderWindow &App){
    for (unsigned int i = 0; i < nCards; ++i){
        cards[i].setPosition (lx + i * 92, ly);
        cards[i].initPicture();
        cards[i].setSize (sf::Vector2f(91,130));
        App.draw(cards[i]);
    }
}

}
#endif // CARDS_H
