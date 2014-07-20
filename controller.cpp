#include "controller.h"
#include "mainwindow.h"
#include <iostream>

Controller::Controller( MainWindow *v ) {
  board = new ChessBoard();
  view = v;
  view->b = board;
  view->setController( this );
  view->showBoard();
  }

void Controller::moveMade( int x1, int y1, int x2, int y2 ) {
  
  bool b = board->makeMove( x1, y1, x2, y2 );
  view->showBoard();
  if( b ) {
    PieceColor c ;
    if( board->getPiece( x2, y2 )->color == WHITE ) c = BLACK;
    else c = WHITE;
    std::cout << "\nMate: " <<  board->isMate( c ) << "\n";
  }
}
