#ifndef _BOARD_H
#define _BOARD_H

#include <SFML/Graphics.hpp>
//#include <iostream>
#include <array>
#include "constants.h"


class Board : public sf::Drawable{

public:

    Board(sf::Color col1 = sf::Color::White, sf::Color col2 = sf::Color::Black);
    
    // Member function that sets Board stuff, can choose square colors in parameters
    void resetColor();
    void selectSquare(int i);


private:

    std::array<sf::RectangleShape, 64> m_boardSquares;
    std::array<bool, 64> isSelected;
    sf::Color selectedColor;
    sf::Color lightColor;
    sf::Color darkColor;

    //void updateSelectedColor(int i,sf::RenderTarget& target);
    
    
    // Draw class on SFML Window
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

#endif