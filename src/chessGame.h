/*
    This header file contains th ChessGame class.
    contains the whole game.
*/

#ifndef _CHESSGAME_H
#define _CHESSGAME_H

#include <SFML/Graphics.hpp>
#include <list> 
#include <cmath> //std::abs()

#include "board.h"
#include "piece.h"

const int directionOffsets[]={-8,8,-1,1,7,-7,9,-9};
const int knightOffsets[]={6,-6,10,-10,15,-15,17,-17};
const int castleMoves[]={2,6,58,62,    3,5,59,61,     0,7,56,63};//4 movimientos de rey, 4 de torre, 4 posicion original de torre
//const int pawnOffsets[]={16,8,9,7};
struct Move{
    int start;
    int end;
    Piece * piece;
    Piece * takes;
};

class ChessGame: public sf::Drawable{
public:
    ChessGame(sf::Color bordCol1, sf::Color bordCol2);

    Piece * getSelectedPiece(){return selectedPiece;}
    bool selectPiece(int pos);
    void moveSelected(int pos);
    void makeMove(Move m);
    void drawLegalMoves(Piece p);
    bool isLegalMove(Move m);
    Piece * isMoveTakingPiece(Move m);

    void restart();
    

private:
    int numSquaresToEdge[64][8];
    Board board;
    std::list<Move> playedMoves;
    std::list<Move> legalMoves;
    std::array<Piece, 16> whitePieces;
    std::array<Piece, 16> blackPieces;
    Piece* selectedPiece=NULL;
    bool playerTurn; // true = White turn, false = Black Turn

    Piece * pieceOnSquare(int square);

    void precomputeNumSquaresToEdge();
    void legalSlidingMoves(Piece &p);
    void legalKnightMoves(Piece &p);
    void legalKingMoves(Piece &p);
    bool isLegalCastle(Move m);
    void legalPawnTakes(Piece &p, int moveOffset, int passantOffset);
    void legalPawnMoves(Piece &p);
    void calculatelegalMovesPiece(Piece &p);
    void updateTakes();
    void recalculateLegalMoves();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};


#endif