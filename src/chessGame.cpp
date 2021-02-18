#include "chessGame.h"
#include "stdio.h"

ChessGame::ChessGame(sf::Color bordCol1 = sf::Color::White, sf::Color bordCol2 = sf::Color::Black)
: board(bordCol1,bordCol2){
    precomputeNumSquaresToEdge();
    restart();
    recalculateLegalMoves();
}

void ChessGame::precomputeNumSquaresToEdge(){
    int index;
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            index=i+8*j;
            numSquaresToEdge[index][0]=j;   //up
            numSquaresToEdge[index][1]=7-j; //down
            numSquaresToEdge[index][2]=i;   //left
            numSquaresToEdge[index][3]=7-i; //right
            numSquaresToEdge[index][4]=std::min(numSquaresToEdge[index][1],numSquaresToEdge[index][2]);//downleft
            numSquaresToEdge[index][5]=std::min(numSquaresToEdge[index][0],numSquaresToEdge[index][3]);//upright
            numSquaresToEdge[index][6]=std::min(numSquaresToEdge[index][1],numSquaresToEdge[index][3]);//downright
            numSquaresToEdge[index][7]=std::min(numSquaresToEdge[index][0],numSquaresToEdge[index][2]);//upleft
        }
    }
}




void ChessGame::restart(){
    playerTurn = true;
    //whitePieces[3].setPiece('Q', true, 33); 
    //whitePieces[0].setPiece('R', true, 35); 
    blackPieces[0].setPiece('R', false, 7);
    blackPieces[1].setPiece('N', false, 6);
    blackPieces[2].setPiece('B', false, 5);
    blackPieces[3].setPiece('K', false, 4);
    blackPieces[4].setPiece('Q', false, 3);
    blackPieces[5].setPiece('B', false, 2);
    blackPieces[6].setPiece('N', false, 1);
    blackPieces[7].setPiece('R', false, 0);

    whitePieces[0].setPiece('R', true, 56); 
    whitePieces[1].setPiece('N', true, 57); 
    whitePieces[2].setPiece('B', true, 58); 
    whitePieces[3].setPiece('Q', true, 59); 
    whitePieces[4].setPiece('K', true, 60); 
    whitePieces[5].setPiece('B', true, 61); 
    whitePieces[6].setPiece('N', true, 62); 
    whitePieces[7].setPiece('R', true, 63); 
    
    for(int i=8;i<16;i++){
        whitePieces[i].setPiece('P', true, 48 +(i-8));
        blackPieces[i].setPiece('P', false, 15 - (i-8) );
    }
}

Piece * ChessGame::pieceOnSquare(int square){
    Piece * p;
    for(int i=0; i<16; i++){
        if(whitePieces[i].getPosition() == square){
            p = &whitePieces[i];
            return p;
        }
        if(blackPieces[i].getPosition() == square){
            p = &blackPieces[i];
            return p;
        }
    }
    return NULL;
}
/*
void ChessGame::updateTakes(){
    for(int i=0; i<16; i++){
        for (int j = 0; j < 16; j++){
            if(whitePieces[i].getPosition()==blackPieces[j].getPosition()){
                if(playerTurn){
                    blackPieces[j].setPosition(-1);
                }
                else{
                    whitePieces[j].setPosition(-1);
                }
            }
        }
    }
}
*/


bool ChessGame::selectPiece(int pos){
    selectedPiece=pieceOnSquare(pos);
    return selectedPiece!=NULL;
}

void ChessGame::moveSelected(int pos){
    if(selectedPiece==NULL) return;

    Move m;
    m.start=selectedPiece->getPosition();
    m.end=pos;
    m.piece=selectedPiece;
    makeMove(m);
    selectedPiece=NULL;
}

void ChessGame::makeMove(Move m){
    if(!isLegalMove(m)) return;
    playedMoves.push_front(m);
    m.piece->setPosition(m.end);
    //castle
    if(m.piece->getType()=='K'){
        for(int i=0; i<4; i++){
            if(m.end==castleMoves[i]){
                pieceOnSquare(castleMoves[i+8])->setPosition(castleMoves[i+4]);
            }
        }
    }
    //updateTakes();
    m.takes=isMoveTakingPiece(m);
    std::cerr<<"takes:"<<m.takes<<"\n";
    if(m.takes!=NULL){
        std::cerr<<"aqui?:\n";
        //std::cerr<<"takes\n";
        m.takes->setPosition(-1);
    }
    //std::cerr<<"aqui?:\n";
    playerTurn=!playerTurn;
    recalculateLegalMoves();
}

void ChessGame::drawLegalMoves(Piece p){
    
    Move m;
    m.start=p.getPosition();
    for(int i=0; i<64; i++){
        m.end=i;
        if(i%8==0){
            std::cerr<<"\n";
        }
        std::cerr<<isLegalMove(m)<<" ";
    }

}

void ChessGame::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.clear(sf::Color::Black);
    target.draw(board);
    for(int i=0;i<16;i++){
        target.draw(whitePieces[i]);
        target.draw(blackPieces[i]);
    }
}

bool ChessGame::isLegalMove(Move m){
    for (auto const& i : legalMoves) {
        if(i.end==m.end&&i.start==m.start){
            return true;
        }
    }
    return false;
}

Piece * ChessGame::isMoveTakingPiece(Move m){
    for (auto const& i : legalMoves) {
        std::cerr<<"isMoveTakingPiece"<<i.takes<<"\n";
        if(i.end==m.end&&i.start==m.start&&i.piece==m.piece){
            
            return i.takes;
        }
    }
    return NULL;
}

void ChessGame::legalSlidingMoves(Piece &p){
    //reina torre alfil
    int startdirIndex=p.getType()=='B' ? 4 : 0;
    int enddirIndex=p.getType()=='R' ? 4 : 8;
    int start=p.getPosition();
    for(int dirIndex=startdirIndex; dirIndex<enddirIndex; dirIndex++){
        for(int distance=1; distance<=numSquaresToEdge[start][dirIndex]; distance++){
            int target=start+directionOffsets[dirIndex]*distance;
            Piece * obstacle = pieceOnSquare(target);
            if(obstacle!=NULL && obstacle->getPlayer()==p.getPlayer()){
                break;
            }
            Move m;
            m.start=start;
            m.end=target;
            m.piece=&p;
            m.takes=NULL;
            if(obstacle!=NULL && obstacle->getPlayer()!=p.getPlayer()){
                m.takes=obstacle;
                legalMoves.push_front(m);
                break;
            }
            legalMoves.push_front(m);
        }
        
    }
}

void ChessGame::legalKnightMoves(Piece &p){
    //caballo
    int start=p.getPosition();
    for(int dirIndex=0; dirIndex<8; dirIndex++){
        /*
        primero compruebo si el caballo está a menos de 2 casillas del borde
        Si lo está no puede hacer el movimiento primario, es decir, el movimiento de 2 casillas de la L
        dirIndex/2 devuelve la dirección del movimiento primario.
        */
        if(numSquaresToEdge[start][dirIndex/2]<2){
            continue;
        }
        /*
        pero si el caballo está pegado al borde no puede hacer el movimiento secundario, el movimiento de 1 casilla de la L
        [2+dirIndex%2-2*(dirIndex/4)] devuelve la direccion del movimiento secundario
        */
        if(numSquaresToEdge[start][2+dirIndex%2-2*(dirIndex/4)]<1){
            continue;
        }
        int target=start+knightOffsets[dirIndex];
        Piece * obstacle= pieceOnSquare(target);
        if(obstacle!=NULL && obstacle->getPlayer()==p.getPlayer()){
            continue;
        }
        Move m;
        m.start=start;
        m.end=target;
        m.piece=&p;
        m.takes=NULL;
        if(obstacle!=NULL && obstacle->getPlayer()!=p.getPlayer()){
            m.takes=obstacle;
            legalMoves.push_front(m);
            continue;
        }
        legalMoves.push_front(m);
    }
}
bool ChessGame::isLegalCastle(Move m){
    int rookPos;
    int rookTarget;
    int kingTarget;
    int travelSquare=0;
    //kingside castle
    if(m.piece->getPlayer()){
        switch(m.end){
            case 58://white queenside
                rookTarget=59;
                kingTarget=58;
                travelSquare=57;
                rookPos=56;
                break;
            case 62://white kingside
                rookPos=63;
                kingTarget=62;
                travelSquare=62;
                rookTarget=61;
                break;
        }
    }
    else{
        switch(m.end){
            case 2://black queenside
                rookTarget=3;
                kingTarget=2;
                travelSquare=1;    for(int i=0; i<16; i++){
        for (int j = 0; j < 16; j++){
            if(whitePieces[i].getPosition()==blackPieces[j].getPosition()){
                if(playerTurn){
                    blackPieces[j].setPosition(-1);
                }
                else{
                    whitePieces[j].setPosition(-1);
                }
            }
        }
    }
                break;
            case 6://black kingside
                rookPos=7;
                kingTarget=6;
                travelSquare=6;
                rookTarget=5;
                break;
        }
    }
    if(travelSquare==0) return false; //not valid
    Piece * rook=pieceOnSquare(rookPos);
    if(rook==NULL||rook->hasMovedBefore()||m.piece->hasMovedBefore()) return false;

    if(pieceOnSquare(rookTarget)!=NULL||pieceOnSquare(kingTarget)!=NULL||pieceOnSquare(travelSquare)!=NULL) return false;
    return true;
}

void ChessGame::legalKingMoves(Piece &p){
    //rey
    int start=p.getPosition();
    Move m;
    m.start=start;
    m.piece=&p;
    for(int dirIndex=0; dirIndex<8; dirIndex++){
        int target=start+directionOffsets[dirIndex];
        if(target<0||target>=64){
            continue;
        }
        Piece * obstacle = pieceOnSquare(target);
        if(obstacle!=NULL && obstacle->getPlayer()==p.getPlayer()){
            continue;
        }
        m.end=target;
        m.takes=NULL;
        if(obstacle!=NULL && obstacle->getPlayer()!=p.getPlayer()){
            m.takes=obstacle;
            legalMoves.push_front(m);
            continue;
        }
        legalMoves.push_front(m);
    }
    for(int i=0; i<4; i++){//castle
        m.end=castleMoves[i];
        if(isLegalCastle(m)){
            std::cerr<<"hey?";
            legalMoves.push_front(m);
        }
    }
}

void ChessGame::legalPawnTakes(Piece &p, int moveOffset, int passantOffset){
    Move m;
    m.start=p.getPosition();
    m.piece=&p;
    if(p.getPlayer())moveOffset=-moveOffset;//if white: move towards black
    m.end=m.start+moveOffset;
    Piece * dangerPiece=pieceOnSquare(m.end);
    m.takes=dangerPiece;
    //normal take
    if(dangerPiece!=NULL&&dangerPiece->getPlayer()!=p.getPlayer()){
        legalMoves.push_front(m);
    }
    //en passant
    dangerPiece=pieceOnSquare(m.start+passantOffset);
    m.takes=dangerPiece;
    //std::cerr<<"analizando peon passant color: "<<p.getPlayer()<<"\n";
    if(dangerPiece!=NULL&&dangerPiece->getPlayer()!=p.getPlayer()){
        //std::cerr<<"    hay una pieza enemiga al lado del peon\n";
        //hay una pieza enemiga al lado del peon
        if(dangerPiece->getType()=='P'&&playedMoves.front().piece==dangerPiece){
            //std::cerr<<"        esa pieza es un peon y ha movido en el ultimo turno\n";
            //std::cerr<<"        ultimo turno: color="<<playedMoves.front().piece->getPlayer()<<"\n";
            //std::cerr<<"        ultimo turno: desde="<<playedMoves.front().start<<"\n";
            //esa pieza es un peon y ha movido en el ultimo turno
            if(std::abs(playedMoves.back().start-playedMoves.back().end)==16){
                //std::cerr<<"            ese peon ha movido 2 cuadrados en 1 turno\n";
                //std::cerr<<"                "<<m.start<<m.end;
                //ese peon ha movido 2 cuadrados en 1 turno
                legalMoves.push_front(m);
            }
        }
    }
}

void ChessGame::legalPawnMoves(Piece &p){
    //pawn
    Move m;
    m.start=p.getPosition();
    m.piece=&p;
    m.takes=NULL;
    int moveOffset;
    //Move 1 square: if not blocked by any piece.
    moveOffset=8;
    if(p.getPlayer())moveOffset=-moveOffset;//if white move backwards
    m.end=m.start+moveOffset;
    Piece * pieceInFront=pieceOnSquare(m.end);
    if(pieceInFront==NULL){
        legalMoves.push_front(m);
    }
    //Move 2 squares: if not blocked and in second rank
    m.end=m.end+moveOffset;
    if(pieceInFront==NULL&&pieceOnSquare(m.end)==NULL){
        if(p.getPlayer()&&p.getPosition()>=48&&p.getPosition()<=55){
            legalMoves.push_front(m);
        }
        if((!p.getPlayer())&&p.getPosition()>=8&&p.getPosition()<=15){
            legalMoves.push_front(m);
        }
    }
    legalPawnTakes(p,7,1);
    legalPawnTakes(p,9,-1);

}

void ChessGame::calculatelegalMovesPiece(Piece &p){
    if(p.getPosition()==-1){
        return;
    }
    if (p.getType()=='Q'||p.getType()=='R'||p.getType()=='B'){
        legalSlidingMoves(p);
    }
    if (p.getType()=='N'){
        legalKnightMoves(p);
    }
    if (p.getType()=='K'){
        legalKingMoves(p);
    }
    if (p.getType()=='P'){
        legalPawnMoves(p);
    }
}

void ChessGame::recalculateLegalMoves(){
    //TODO: position -1 is weird
    legalMoves.clear();
    for(int i=0; i<16; i++){
        if(playerTurn){
            calculatelegalMovesPiece(whitePieces[i]);
        }
        else{
            calculatelegalMovesPiece(blackPieces[i]);
        }
    }
}