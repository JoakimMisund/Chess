#include "ChessPiece.h"

class Square {

 private:
  
  Piece* piece;
  

 public:
  
  PieceColor color;
  int x, y;

  Square( Piece* piece, PieceColor color );
  Square( PieceColor color );
  Square();
  Piece* getPiece();
  void setPiece( Piece* piece );
  bool isEmpty();
  Piece* removePiece();
  PieceColor getColor();

};
