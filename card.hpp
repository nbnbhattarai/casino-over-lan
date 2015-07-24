#ifndef CARD_H
#define CARD_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#define PICTURES_PATH "/"

#include <iostream>
namespace cardgame{

enum CardValue {TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, J, QUEEN, KING, ACE, JOKER};
enum CardType {HEART,DIAMOND,CLUB,SPADE};

/** This structure is used to send card over internet
**/
struct send_card{
    CardValue value;
    CardType type;
};

class Card : public sf :: RectangleShape{
        private :
            CardValue Value;
            CardType Type;
            sf :: Texture PictureTexture;
            std :: string PicturePath;

        public :
            Card (CardValue = ACE,CardType = HEART);
            Card (send_card sc);
            Card (Card &c);
            ~Card ();
            void setValue (CardValue);
            CardValue getValue (void);
            void setType (CardType);
            CardType getType (void);
            void setPicturePath (std :: string);
            std :: string getPicturePath (void);
			int initPicture (void);
            operator send_card ();
};

Card :: operator send_card (){
                send_card sc;
                sc.value = this->Value;
                sc.type = this->Type;
                return sc;
            }
Card :: Card (CardValue value, CardType type)
{
    Type = type;
    Value = value;
    this -> setSize (sf :: Vector2f (150,215));
    PicturePath = "./Pictures/cards/";
  //  this->initPicture();
}

Card::Card (Card &c){
    this->Value = c.getValue();
    this->Type = c.getType();
    PicturePath = "./Pictures/cards/";
//    this->initPicture();
}

Card :: Card (send_card sc){
    this->Value = sc.value;
    this->Type = sc.type;
    PicturePath = "./Pictures/cards/";
  //  this->initPicture();
}

Card :: ~Card ()
{
    // nothing to do
}


void Card :: setValue (CardValue value)
{
    Value = value;
}

CardValue Card :: getValue (void)
{
    return Value;
}

void Card :: setType (CardType type)
{
    Type = type;
}

CardType Card :: getType (void)
{
    return Type;
}

void Card :: setPicturePath (std :: string path)
{
    PicturePath = path;
}

std :: string Card :: getPicturePath (void)
{
    return PicturePath;
}

int Card :: initPicture (void)
{
    std :: string PicturePath;
    char suffix[] = "HDCS";
    char value[] = "  23456789TJQKA";
    if (this -> Value == JOKER){

    }else{
        PicturePath = this->PicturePath;
        PicturePath += value[Value];
        PicturePath += suffix [Type];
        PicturePath += "-150.png";
    }
    //std :: cout << "card picture init from : " <<  PicturePath << std :: endl;
    if(!PictureTexture.loadFromFile (PicturePath))
        throw cardgame::Exception(cardgame::Exception::FILE_CANNOT_LOAD,PicturePath);

    setTexture (&PictureTexture);

    return 1;
    }
}
#endif
