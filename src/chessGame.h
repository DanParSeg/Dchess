/*
    This header file contains th ChessGame class.
    contains the whole game.
*/

#ifndef _CHESSGAME_H
#define _CHESSGAME_H

#include <SFML/Graphics.hpp>
#include <list> 
#include <cmath> //std::abs()
#include <iostream>

#include "board.h"
#include "piece.h"
#include "chessMove.h"


const int directionOffsets[]={-8,8,-1,1,7,-7,9,-9};//up down left right downleft upright downright upleft
const int knightOffsets[]={-17,-15,15,17,-10,6,-6,10};//up(left right) down(left right) left(up down) right(up down)
const int castleMoves[]={2,6,58,62,    3,5,59,61,     0,7,56,63};//4 movimientos de rey, 4 de torre, 4 posicion original de torre

/*
struct Move{
    int start;
    int end;
    Piece * piece;
    Piece * takes;
};
*/

class ChessGame: public sf::Drawable{
public:
    ChessGame(sf::Color bordCol1, sf::Color bordCol2);

    Piece * getSelectedPiece(){return selectedPiece;}
    bool selectPiece(int pos);
    void moveSelected(int pos);
    void makeMove(ChessMove m);
    void undoMove();
    void drawLegalMoves(Piece p);
    void resetColorBoard(){board.resetColor();};
    bool isLegalMove(ChessMove m);
    Piece * isMoveTakingPiece(ChessMove m);

    void restart();
    

private:
    int numSquaresToEdge[64][8];
    Board board;
    std::list<ChessMove> playedMoves;
    std::list<ChessMove> legalMoves;
    std::array<Piece, 16> whitePieces;
    std::array<Piece, 16> blackPieces;
    Piece* selectedPiece=NULL;
    bool playerTurn; // true = White turn, false = Black Turn

    Piece * pieceOnSquare(int square);
    void debugPrintMove(ChessMove m);
    void precomputeNumSquaresToEdge();
    void legalSlidingMoves(Piece &p);
    void legalKnightMoves(Piece &p);
    void legalKingMoves(Piece &p);
    bool isLegalCastle(ChessMove m);
    void legalPawnTakes(Piece &p, int dirIndex);
    void legalPawnMoves(Piece &p);
    void calculatelegalMovesPiece(Piece &p);
    void updateTakes();
    void recalculateLegalMoves();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};


#endif