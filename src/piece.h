
/*
    This header file contains the Piece class.
*/

#ifndef _PIECE_H
#define _PIECE_H

#include <SFML/Graphics.hpp>
#include "pieceSprites.h"
#include "constants.h"

class Piece : public sf::Drawable{

public:

    Piece(char type='P', bool player=true, int pos=-1)
    : m_type{type}, m_player{player},
    m_position{-1}
    { }

    void setPiece(char type, bool player, int pos);

    void setType(char t){m_type = t; setTexture();}
    char getType()       {return m_type;}

    void setPlayer(bool p){m_player = p; setTexture();}
    bool getPlayer()       {return m_player;}

    void setPosition(int pos){m_position = pos; move(); m_hasMovedBefore=true;}//activates flag hasMovedBefore
    int getPosition()        {return m_position;}

    bool hasMovedBefore(){return m_hasMovedBefore;}

private:
    sf::Sprite m_sprite;

    char m_type; //'K'=King , 'Q' = Queen , 'R' = Rook , 'B' = Bishop , 'N' = Knight , 'P' = Pawn
    bool m_player; // true == White , false == Black
    int m_position; // 0-63 board, -1 dead
    bool m_hasMovedBefore;

    void setTexture();
    void move();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {   if(m_position!=-1) target.draw(m_sprite);  }
};

#endif