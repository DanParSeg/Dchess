#include <SFML/Graphics.hpp>
#include "constants.h"
#include "board.h"
#include "piece.h"
#include "fenParser.h"
#include "chessGame.h"
#include "stdio.h"

int main()
{
    ChessGame board(sf::Color(240, 217, 181),sf::Color(148, 111, 81));

    sf::RenderWindow window(sf::VideoMode(SQUARESIZE*8, SQUARESIZE*8), "mmmmmmmmmmmmmmmmmmmm");
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::MouseButtonPressed){
                if(event.mouseButton.button == sf::Mouse::Left){
                    if((0 <= event.mouseButton.x) && (event.mouseButton.x <= SQUARESIZE*8) && (0 <= event.mouseButton.y) && (event.mouseButton.y <= SQUARESIZE*8)){
                        int buttonPos{(event.mouseButton.x/SQUARESIZE) + (event.mouseButton.y/SQUARESIZE * 8)};
                        if(board.getSelectedPiece()==NULL){
                            if(board.selectPiece(buttonPos))
                                board.drawLegalMoves(*board.getSelectedPiece());
                            //window.display();
                        }
                        else{
                            board.resetColorBoard();
                            board.moveSelected(buttonPos);
                        }

                    }
                }
            }
        }
        window.clear();
        window.draw(board);
        window.display();
        
    }

    return 0;
}
