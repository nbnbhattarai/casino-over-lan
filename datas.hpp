#ifndef datas_H
#define datas_H

#include <SFML/Network.hpp>
#include "card.hpp"
#include "cards.hpp"

namespace cardgame{

    enum screenId{
        EXIT = -1,
        MAINMENUSCREEN,
        NEWGAMESCREEN,
        JOINGAMESCREEN,
        HIGHSCORESCREEN,
        HELPANDABOUTSCREEN,
        EXITCONFIRMSCREEN,
        GAMESCREEN
    };

    namespace datas{

        int myId = 0;
        /// this is used for exit confirm screen to return back to this window
        int currentRunningWindow;

        unsigned short PORT = 5002;
        sf::TcpSocket socket[4];

        /// list of name of players
        /// index myId is for current user, server has myId = 0
        std::string playerName[4];

        /// to verify whether this is server side or client side
        bool iAmServer;

        cardgame::Cards allCard[4];
        bool shown[13];

        cardgame::send_card send_cards[13];

        /// this card is used to send one card over internet
        cardgame::send_card *sendCard = new cardgame::send_card;

        /// this card is send automatically after user has his turn and is card that user selects
        cardgame::send_card *my_shown_card = new cardgame::send_card;

        /// this is shown card by other users, which server sends to other clients
        cardgame::send_card *shown_cards = new cardgame::send_card[4];

        bool myTurn;
        bool threadRunning = true;

    }
}
#endif // datas_H
