#include "controller.h"
#include "mainwindow.h"
#include <iostream>

Controller::Controller( MainWindow *v ) {
  board = new ChessBoard();
  view = v;
  view->b = board;
  view->setController( this );
  view->showBoard();
  inMove = WHITE;
}

void Controller::moveMade( int x1, int y1, int x2, int y2 ) {
  
  if( board->getPiece( x1, y1 )->color != inMove ) return;
  bool b = board->makeMove( x1, y1, x2, y2 );
  view->showBoard();
  if( b ) {
    PieceColor c ;
    if( board->getPiece( x2, y2 )->color == WHITE ) c = BLACK;
    else c = WHITE;
    bool a = board->isMate( inMove == WHITE ? BLACK : WHITE );
    
    
    
    if( a )  {
      if( inMove == WHITE ) {
	view->reportMate( QString( "White won") );
      } else {
	view->reportMate( QString( "Black won") );
      }
    }    
    inMove = (inMove == WHITE) ? BLACK : WHITE ;
  }
}
