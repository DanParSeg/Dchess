#ifndef _FEN_PARSER_H
#define _FEN_PARSER_H

#include "piece.h"
#include <iostream>

namespace fenParser{
    //input: null terminated string, Piece array
    bool parseFenString(char * fen, Piece[32]);
}


#endif