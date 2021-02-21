#include "fenParser.h"

bool isValidDigit(char c){
    if(c>='0'&&c<='8'){
        return true;
    }
    return false;
}
int toDigit(char c){
    return c-'0';
}
Piece toPiece(char c,int pos){
    Piece p;
    switch(c){
        case 'P':
            p.setPiece('P',1,pos);
            return p;
        case 'R':
            p.setPiece('R',1,pos);
            return p;
        case 'N':
            p.setPiece('N',1,pos);
            return p;
        case 'B':
            p.setPiece('B',1,pos);
            return p;
        case 'K':
            p.setPiece('K',1,pos);
            return p;
        case 'Q':
            p.setPiece('Q',1,pos);
            return p;
        case 'p':
            p.setPiece('P',0,pos);
            return p;
        case 'r':
            p.setPiece('R',0,pos);
            return p;
        case 'n':
            p.setPiece('N',0,pos);
            return p;
        case 'b':
            p.setPiece('B',0,pos);
            return p;
        case 'k':
            p.setPiece('K',0,pos);
            return p;
        case 'q':
            p.setPiece('Q',0,pos);
            return p;
    }
    return p;
}

bool fenParser::parseFenString(char * fen, Piece pieceArr[32]){
    std::cerr<<fen;
    int pieceNumber=0;
    int position=0;
    int i;
    for(i=0; fen[i]!=0||position<64; i++){
        char c=fen[i];
        std::cerr<<" "<<c;
        std::cerr<<position;
        if(isValidDigit(c)){
            position+=toDigit(c);
            continue;
        }
        if(c=='/'){
            continue;
        }
        pieceArr[pieceNumber]=toPiece(c,position);
        pieceNumber++;
        position++;
    }
    std::cerr<<"\npos"<<pieceArr[25].getType();
    return true;
}