#ifndef _FEN_PARSER_H
#define _FEN_PARSER_H

#include "piece.h"

namespace fenParser{
    //input: null terminated string, Piece array
    bool parseFenString(char * fen, Piece[32]);
}


#endif