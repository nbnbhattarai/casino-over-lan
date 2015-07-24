#ifndef SERVERSIDE_HPP
#define SERVERSIDE_HPP

#include <SFML/Network.hpp>
#include <cstdlib>
#include <thread>
#include <X11/Xlib.h>
#include "datas.hpp"
#include "card.hpp"

namespace cardgame{
void swap(cardgame::send_card &c1, cardgame::send_card &c2);
void nextTurn(int&);

void shuffle (cardgame::send_card *c, int n);

void Server(){
    XInitThreads();

    std::cout << "This is inside server thread." << std::endl;
    int turn = rand() % 4;
    std::size_t received;
    cardgame::send_card cards[52];

    for (int i = 1; i <= 52; i++){
        cards[i-1].value = static_cast<cardgame::CardValue>(i%13 + 2);
        cards[i-1].type = static_cast<cardgame::CardType>(i%4);
    }

    shuffle(cards, 52);

    for (int i = 0; i < 52; ++i){
        cardgame::datas::allCard[i/13][i%13] = cards[i];
    }

    for (int i = 1; i < 4; ++i){
        for (int j = 0; j < 13; ++j)
            cardgame::datas::send_cards[j] = cards[i*13+j];
        if (cardgame::datas::socket[i].send(cardgame::datas::send_cards, sizeof(cardgame::send_card) * 13) != sf::Socket::Done){
            throw cardgame::Exception(cardgame::Exception::CANNOT_SEND_FILE,cardgame::datas::playerName[i]);
        }
    }

    while (cardgame::datas::threadRunning){
        std::this_thread::sleep_for (std::chrono::milliseconds(2000));

        if (turn == 0){
            cardgame::datas::myTurn = true;
            while (cardgame::datas::myTurn)
                ;

            for (int i = 1; i < 4; ++i)
                cardgame::datas::socket[i].send(cardgame::datas::my_shown_card,sizeof(cardgame::send_card));

            continue;
        }else{
            for (int i = 1; i < 4; ++i)
                cardgame::datas::socket[turn].send(&turn,sizeof(int));

            cardgame::datas::socket[turn].receive(cardgame::datas::sendCard, sizeof(cardgame::send_card), received);

            /// receive card shown from a client
            cardgame::datas::shown_cards[turn] = static_cast<cardgame::send_card>(cardgame::datas::sendCard[0]);
            for (int i = 1; i < 4; ++i){
                if ( i == turn )
                    continue;
                /// and send received shown card of client to other client
                cardgame::datas::socket[i].send(cardgame::datas::sendCard, sizeof(cardgame::send_card));
            }
        }
        nextTurn(turn);
    }
}

void nextTurn (int &turn)
{
    if (turn == 3)
        turn = 0;
    else
        turn++;
}

void swap(cardgame::send_card &c1, cardgame::send_card &c2){
    cardgame::send_card c = c1;
    c1 = c2;
    c2 = c;
}
void shuffle(cardgame::send_card *c, int n){
    int a, b;
    for (int i = 0; i < 1000; ++i){
        a = rand() % n;
        b = rand() % n;
        swap (c[a],c[b]);
    }
}

}
#endif // SERVERSIDE_HPP
