
/*
    This code file contains member functions of piece.h
*/

#include "piece.h"

void Piece::setPiece(char type, bool player, int pos){
    setType(type);
    setPlayer(player);
    setPosition(pos); //m_moved true
    m_hasMovedBefore=false;
}

void Piece::move(){
    if(m_position<=-1 || 64<=m_position){
        m_position = -1;
        m_sprite.setColor(sf::Color(0x00000000));
    }
    m_sprite.setPosition(sf::Vector2f((m_position % 8) * SQUARESIZE + SQUARESIZE/2, (m_position / 8) * SQUARESIZE + SQUARESIZE/2));

    return;
}

void Piece::setTexture(){
    m_sprite = sf::Sprite();
    switch (m_type)
    {
        case 'K':
            m_sprite.setTexture(m_player ? PieceTextures::whiteKing : PieceTextures::blackKing);
            break;
        case 'Q':
            m_sprite.setTexture(m_player ? PieceTextures::whiteQueen : PieceTextures::blackQueen);
            break;
        case 'R':
            m_sprite.setTexture(m_player ? PieceTextures::whiteRook : PieceTextures::blackRook);
            break;
        case 'B':
            m_sprite.setTexture(m_player ? PieceTextures::whiteBishop : PieceTextures::blackBishop);
            break;
        case 'N':
            m_sprite.setTexture(m_player ? PieceTextures::whiteKnight : PieceTextures::blackKnight);
            break;
        case 'P':
            m_sprite.setTexture(m_player ? PieceTextures::whitePawn : PieceTextures::blackPawn);
            break;
        default:
            //TODO:error
            break;
    }
    m_sprite.setOrigin(sf::Vector2f(m_sprite.getTexture()->getSize().x/2 , m_sprite.getTexture()->getSize().y/2));
    //m_sprite.setScale(sf::Vector2f(0.9f,0.9f));
}

