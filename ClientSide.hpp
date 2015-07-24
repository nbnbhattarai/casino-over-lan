#ifndef CLIENTSIDE_HPP
#define CLIENTSIDE_HPP

#include <SFML/Network.hpp>
#include <X11/Xlib.h>
#include "card.hpp"
#include <thread>

namespace cardgame {
    void Client (){
        XInitThreads();

        int turn;
        std::size_t received;

        /// receive 13 cards that server sends to play game
        if(cardgame::datas::socket[0].receive(cardgame::datas::send_cards,sizeof(cardgame::send_card) * 13,received) != sf::Socket::Done){
            throw cardgame::Exception(cardgame::Exception::CANNOT_RECEIVE_FILE," [that server is sending]");
        }

        for (int i = 0; i < 13; ++i){
            cardgame::datas::allCard[0][i] = cardgame::datas::send_cards[i];
            std::cout << "received card : " << cardgame::datas::send_cards[i].value << " and type : " << cardgame::datas::send_cards[i].type << std::endl;
        }

        while (cardgame::datas::threadRunning){
            cardgame::datas::socket[0].receive(&turn, sizeof(int),received);
            if (turn == cardgame::datas::myId){
                cardgame::datas::myTurn = true;
            }
            else{
                cardgame::datas::myTurn = false;
            }

            std::this_thread::sleep_for (std::chrono::milliseconds(2000));
        }
    }
}
#endif // CLIENTSIDE_HPP
