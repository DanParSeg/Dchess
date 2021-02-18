/*
    This code file contains member functions of board.h
*/

#include "board.h"



Board::Board(sf::Color col1, sf::Color col2){

    selectedColor=sf::Color(32, 79, 24);
    lightColor=col1;
    darkColor=col2;
    resetColor();
}

// Member function that sets Board stuff, can choose square colors in parameters
void Board::resetColor(){
    for(int i=0; i<8;i++){
        bool tmpColor = ((i % 2)==0)?true:false;
        for(int j=0; j<8;j++){
            m_boardSquares[j + (i * 8)].setPosition(sf::Vector2f( j*SQUARESIZE, i*SQUARESIZE ));
            m_boardSquares[j + (i * 8)].setSize(sf::Vector2f(SQUARESIZE, SQUARESIZE));
            m_boardSquares[j + (i * 8)].setFillColor(tmpColor ? lightColor : darkColor);
            tmpColor = !tmpColor;
        }
    }
}

void Board::selectSquare(int i){
    m_boardSquares[i].setFillColor(selectedColor);
}

// Draw class on SFML Window
void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    for(int i=0;i<64;i++){
        target.draw(m_boardSquares[i]);
    }
}