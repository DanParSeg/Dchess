#ifndef _CHESS_MOVE_H
#define _CHESS_MOVE_H

#include <iostream>
#include "piece.h"


class ChessMove{
public:
    ChessMove(){}
    int getStart() const{return m_start;}
    void setStart(uint8_t start);

    int getEnd() const{return m_end;}
    void setEnd(uint8_t end);

    Piece * getPiece() const{return m_piece;}
    void setPiece(Piece * p){m_piece=p;}

    Piece * getTaken() const{return m_taken;}
    void setTaken(Piece * p){m_taken=p;}

    bool isCastle() const {return m_castle;}

    //void setPlayer(bool player){m_player=player;}

    bool isCapture() const{return m_taken!=NULL;}
/*
    void setFlags(bool castle=false, bool passant=false, bool promote=false){
        m_castle=castle;
        m_passant=passant;
        m_promote=promote;
    }
*/

private:
    uint8_t m_start;
    uint8_t m_end;
    Piece * m_taken=NULL;
    Piece * m_piece=NULL;
    bool m_castle=false;
    bool m_passant=false;
    bool m_promote=false;
    //bool m_player;
};



#endif