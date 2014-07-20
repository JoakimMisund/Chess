#include <string>

enum PieceType{ PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING };

enum PieceColor{ WHITE, BLACK };

//i should make a struct for the pieces

struct Piece {

  //value to determin if a piece is in play, or taken.
  bool inPlay;
  int nrOfMoves;
  
  PieceType type;
  PieceColor color;
  int x, y;
  
  Piece( PieceType t, PieceColor c);
  Piece( PieceType t, PieceColor c, bool ip);

  std::string toString();

};
