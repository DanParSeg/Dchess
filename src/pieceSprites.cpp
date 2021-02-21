/*
    This code file contains static member initialisations
    of pieceTextures.h
*/

#include "pieceSprites.h"

sf::Texture PieceTextures::loadTexture(std::string str){
    sf::Texture tmp;
    if (!tmp.loadFromFile(str)){
        //std::cout << "Error loading file\n";
    }
    return tmp;
}

sf::Texture PieceTextures::blackKing = PieceTextures::loadTexture("pieceSet/bK.png");
sf::Texture PieceTextures::blackQueen = PieceTextures::loadTexture("pieceSet/bQ.png");
sf::Texture PieceTextures::blackRook = PieceTextures::loadTexture("pieceSet/bR.png");
sf::Texture PieceTextures::blackKnight = PieceTextures::loadTexture("pieceSet/bN.png");
sf::Texture PieceTextures::blackBishop = PieceTextures::loadTexture("pieceSet/bB.png");
sf::Texture PieceTextures::blackPawn = PieceTextures::loadTexture("pieceSet/bP.png");

sf::Texture PieceTextures::whiteKing = PieceTextures::loadTexture("pieceSet/wK.png");
sf::Texture PieceTextures::whiteQueen = PieceTextures::loadTexture("pieceSet/wQ.png");
sf::Texture PieceTextures::whiteRook = PieceTextures::loadTexture("pieceSet/wR.png");
sf::Texture PieceTextures::whiteKnight = PieceTextures::loadTexture("pieceSet/wN.png");
sf::Texture PieceTextures::whiteBishop = PieceTextures::loadTexture("pieceSet/wB.png");
sf::Texture PieceTextures::whitePawn = PieceTextures::loadTexture("pieceSet/wP.png");