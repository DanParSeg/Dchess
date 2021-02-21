#include "chessMove.h"
void ChessMove::setStart(uint8_t start){
    if(start>=64){
        std::cerr<<"ChessMove error: move start "<<(int)start<<"!!!\n";
        return;
    }
    m_start=start;
}
void ChessMove::setEnd(uint8_t end){
    if(end>=64){
        std::cerr<<"ChessMove error: move end "<<(int)end<<"!!!\n";
        return;
    }
    m_end=end;
}