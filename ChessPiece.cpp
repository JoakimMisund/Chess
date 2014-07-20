#include "ChessPiece.h"
#include <string>
#include <cstdio>

//
// Methods of the structure "Piece"

Piece::Piece( PieceType t, PieceColor c ): type(t), color(c)  {
  
  inPlay = true;
  nrOfMoves = 0;
}

Piece::Piece( PieceType t, PieceColor c, bool ip): type(t), color(c) {

  inPlay = ip;
  nrOfMoves = 0;
}

std::string Piece::toString() {

  int i = type;
  int j = color;
  int k = inPlay;

  char* t = new char[2];
  sprintf( t, "%d", i);

  char* c = new char[2];
  sprintf( c, "%d", j );
  
  char* k1 = new char[2];
  sprintf( k1, "%d", k );

  std::string msg = std::string(t) + c + k1;

  delete t;
  delete c;
  delete k1;
  
  return msg;

}

//
//end 
