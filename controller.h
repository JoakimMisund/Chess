#include "ChessPiece.h"

#ifndef CHESSBOARD_H
#define CHESSBOARD_H



class ChessBoard;
class MainWindow;

#ifndef CONTROLLER_H
#define CONTROLLER_H

class Controller
{

 private:
  MainWindow *view;
  ChessBoard *board;
  PieceColor inMove;
  

 public:
    Controller( MainWindow *v );
    void moveMade( int x1, int y1, int x2, int y2 );
    
};

#endif // CONTROLLER_H

#endif
