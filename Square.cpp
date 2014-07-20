#include "Square.h"
#include <cstdlib>

Square::Square( Piece* piece, PieceColor color ) {
  
  piece = NULL;
  this->piece = piece;
  this->color = color;
}

Square::Square( PieceColor color ) {
  
  piece = NULL;
  this->color = color;
}

Square::Square() {
  
  piece = NULL;
  color = WHITE;
}

Piece* Square::getPiece() {
  
  return piece;
}

void Square::setPiece( Piece* piece ) {
  
  this->piece = piece;
}

bool Square::isEmpty() {

  return piece == NULL;
}

Piece* Square::removePiece() {
  
  Piece* tmp = piece;
  piece = NULL;
  return tmp;
}

PieceColor Square::getColor() {
  
  return color;
}
