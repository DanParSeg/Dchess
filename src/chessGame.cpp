#include "chessGame.h"
//#include "stdio.h"

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

bool ChessGame::selectPiece(int pos){
    selectedPiece=pieceOnSquare(pos);
    return selectedPiece!=NULL;
}

void ChessGame::moveSelected(int pos){
    if(selectedPiece==NULL) return;

    ChessMove m;
    m.setStart(selectedPiece->getPosition());
    m.setEnd(pos);
    m.setPiece(selectedPiece);
    makeMove(m);
    selectedPiece=NULL;
}

/*
void ChessGame::undoMove(){
    ChessMove m=playedMoves.front();
    playedMoves.pop_front();
    m.piece->setPosition(m.start);
    if(m.takes!=NULL){
        m.takes->setPosition(m.end);
    }
    playerTurn=!playerTurn;
}
*/

void ChessGame::makeMove(ChessMove m){
    //debug
    std::cerr<<"legal moves:\n";
    for (auto const& i : legalMoves) {
        debugPrintMove(i);
    }
    std::cerr<<"\nmove:\n";
    debugPrintMove(m);



    //si es legal muevo la pieza y añado a la lista de movimientos
    if(!isLegalMove(m)) return;
    m.setTaken(isMoveTakingPiece(m));//si el movimiento captura una pieza, añadelo al movimiento
    playedMoves.push_front(m);
    m.getPiece()->setPosition(m.getEnd());
    //mueve la ficha capturada
    
    if(m.isCapture()){
        std::cerr<<"\033[1;31m"<<"takes"<<"\033[0m\n";
        debugPrintMove(m);
        m.getTaken()->setPosition(-1);
    }
    
    //cambia de turno y recalcula movimientos legales
    playerTurn=!playerTurn;
    recalculateLegalMoves();
    //m.piece->setPosition(m.end);
    //castle
    /*
    if(m.isCastle()){
        pieceOnSquare(castleMoves[i+8])->setPosition(castleMoves[i+4]);
    }
    */
    /*
    if(m.getPiece()->getType()=='K'){
        for(int i=0; i<4; i++){
            if(m.end==castleMoves[i]&&(m.start==60||m.start==4)){
                pieceOnSquare(castleMoves[i+8])->setPosition(castleMoves[i+4]);
            }
        }
    }
    */
    //updateTakes();
}

void ChessGame::drawLegalMoves(Piece p){
    ChessMove m;
    m.setStart(p.getPosition());
    board.selectSquare(p.getPosition());
    for(int i=0; i<64; i++){
        m.setEnd(i);
        if(i%8==0){
            std::cerr<<"\n";
        }
        bool t=isLegalMove(m);
        std::cerr<<t<<" ";
        if(t){
            board.selectSquare(i);
        }
    }
    std::cerr<<"\n";
}

void ChessGame::debugPrintMove(ChessMove m){
    std::cerr<<m.getPiece()->getType();
    std::cerr<<m.getStart();
    std::cerr<<"-";
    std::cerr<<m.getEnd();
    if(m.isCapture()){
        std::cerr<<" x:";
        std::cerr<<m.getTaken()->getType()<<m.getTaken()->getPosition();
    }
    std::cerr<<"\n";
}

void ChessGame::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.clear(sf::Color::Black);
    target.draw(board);

    for(int i=0;i<16;i++){
        target.draw(whitePieces[i]);
        target.draw(blackPieces[i]);
    }
}

bool ChessGame::isLegalMove(ChessMove m){
    for (auto const& i : legalMoves) {
        if(i.getEnd()==m.getEnd()&&i.getStart()==m.getStart()){
            return true;
        }
    }
    return false;
}

Piece * ChessGame::isMoveTakingPiece(ChessMove m){
    for (auto const& i : legalMoves) {
        if(i.getEnd()==m.getEnd()&&i.getStart()==m.getStart()&&i.getPiece()==m.getPiece()){
            return i.getTaken();
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
            ChessMove m;
            m.setStart(start);
            m.setEnd(target);
            m.setPiece(&p);
            if(obstacle!=NULL && obstacle->getPlayer()!=p.getPlayer()){
                m.setTaken(obstacle);
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
        ChessMove m;
        m.setStart(start);
        m.setEnd(target);
        m.setPiece(&p);
        if(obstacle!=NULL && obstacle->getPlayer()!=p.getPlayer()){
            m.setTaken(obstacle);
        }
        legalMoves.push_front(m);
    }
}
bool ChessGame::isLegalCastle(ChessMove m){
    int rookPos;
    int rookTarget;
    int kingTarget;
    int travelSquare=0;
    //kingside castle
    if(m.getPiece()->getPlayer()){
        switch(m.getEnd()){
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
        switch(m.getEnd()){
            case 2://black queenside
                rookTarget=3;
                kingTarget=2;
                travelSquare=1;
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
    if(rook==NULL||rook->hasMovedBefore()||m.getPiece()->hasMovedBefore()) return false;

    if(pieceOnSquare(rookTarget)!=NULL||pieceOnSquare(kingTarget)!=NULL||pieceOnSquare(travelSquare)!=NULL) return false;
    return true;
}

void ChessGame::legalKingMoves(Piece &p){
    //rey
    int start=p.getPosition();
    ChessMove m;
    m.setStart(start);
    m.setPiece(&p);
    for(int dirIndex=0; dirIndex<8; dirIndex++){
        if(numSquaresToEdge[start][dirIndex]<1){
            continue;
        }
        int target=start+directionOffsets[dirIndex];
        if(target<0||target>=64){
            continue;
        }
        Piece * obstacle = pieceOnSquare(target);
        if(obstacle!=NULL && obstacle->getPlayer()==p.getPlayer()){
            continue;
        }
        m.setEnd(target);
        if(obstacle!=NULL && obstacle->getPlayer()!=p.getPlayer()){
            m.setTaken(obstacle);
        }
        legalMoves.push_front(m);
    }
    for(int i=0; i<4; i++){//castle
        m.setEnd(castleMoves[i]);
        if(isLegalCastle(m)){
            legalMoves.push_front(m);
        }
    }
}

void ChessGame::legalPawnTakes(Piece &p, int dirIndex){
    ChessMove m;
    m.setStart(p.getPosition());
    m.setPiece(&p);
    
    int moveOffset=directionOffsets[dirIndex];
    int passantOffset=moveOffset+8;
    

    if(p.getPlayer()&&moveOffset>0){//if white and wants to take backwards
        return;
    }
    if(!p.getPlayer()&&moveOffset<0){//if black and wants to take backwards
        return;
    }
    if(numSquaresToEdge[m.getStart()][dirIndex]<1){//if too close to the edge
        return;
    }

    m.setEnd(m.getStart()+moveOffset);

    Piece * dangerPiece=pieceOnSquare(m.getEnd());
    m.setTaken(dangerPiece);
    //normal take
    if(dangerPiece!=NULL&&dangerPiece->getPlayer()!=p.getPlayer()){
        legalMoves.push_front(m);
    }
    //en passant
    dangerPiece=pieceOnSquare(m.getStart()+passantOffset);
    m.setTaken(dangerPiece);
    if(dangerPiece!=NULL&&dangerPiece->getPlayer()!=p.getPlayer()){
        if(dangerPiece->getType()=='P'&&playedMoves.front().getPiece()==dangerPiece){
            if(std::abs(playedMoves.back().getStart()-playedMoves.back().getEnd())==16){
                legalMoves.push_front(m);
            }
        }
    }
}

void ChessGame::legalPawnMoves(Piece &p){
    //pawn
    ChessMove m;
    m.setStart(p.getPosition());
    m.setPiece(&p);
    int moveOffset;
    //Move 1 square: if not blocked by any piece.
    moveOffset=8;
    if(p.getPlayer())moveOffset=-moveOffset;//if white move backwards
    m.setEnd(m.getStart()+moveOffset);
    Piece * pieceInFront=pieceOnSquare(m.getEnd());
    if(pieceInFront==NULL){
        legalMoves.push_front(m);
    }
    //Move 2 squares: if not blocked and in second rank
    m.setEnd(m.getEnd()+moveOffset);
    if(pieceInFront==NULL&&pieceOnSquare(m.getEnd())==NULL){
        if(p.getPlayer()&&p.getPosition()>=48&&p.getPosition()<=55){
            legalMoves.push_front(m);
        }
        if((!p.getPlayer())&&p.getPosition()>=8&&p.getPosition()<=15){
            legalMoves.push_front(m);
        }
    }
    legalPawnTakes(p,4);
    legalPawnTakes(p,5);
    legalPawnTakes(p,6);
    legalPawnTakes(p,7);

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
    
    legalMoves.clear();
    
    for(int i=0; i<16; i++){
        
        calculatelegalMovesPiece(whitePieces[i]);
        calculatelegalMovesPiece(blackPieces[i]);
        
        /*
        if(playerTurn){
            calculatelegalMovesPiece(whitePieces[i]);
        }
        else{
            calculatelegalMovesPiece(blackPieces[i]);
        }
        */
    }
    
    
}