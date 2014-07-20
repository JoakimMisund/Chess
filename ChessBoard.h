#include "Square.h"
#include <stack>
#include <vector>

enum Player { PLAYER_BLACK, PLAYER_WHITE, PC_WHITE, PC_BLACK };

struct Move {
  
  int from_x, from_y;
  int to_x, to_y;
  
  Piece* pieceTaken;
  
  Move( int fx, int fy, int tx, int ty, Piece* taken );
  Move( int fx, int fy, int tx, int ty );
};

const int BOARD_WIDTH_HEIGHT = 8;


class ChessBoard {

 private:
  std::stack<Move> moves;
  Square board[BOARD_WIDTH_HEIGHT][BOARD_WIDTH_HEIGHT];
  std::vector<Piece*> whitePieces;
  std::vector<Piece*> blackPieces;
  
  Square* findKing( PieceColor color );
  bool checkIfCanMoveTo( PieceColor color, int to_x, int to_y );
  bool playersKingInCheck( PieceColor playerInMove );
  bool checkDiagonalLine( Move move );
  bool checkHorisontalOrVerticalLine( Move move );
  bool validatePawnMove( Move move );
  bool validateKnightMove( Move move );
  bool validateKingMove( Move move );
  bool validateMove( Move move );
  bool validatePawnVerticalDirection( PieceColor color, int to_y, int from_y );

  void initializeBoard();
  PieceType getPieceType( int width );
  Piece* removePiece( int x, int y );
  void setPiece( int x, int y, Piece* piece );
  Square* getSquare( int x, int y );
  std::vector<Piece*> findThreatheningPieces( Piece* p );
  
 public:
  
  ChessBoard();

  bool makeMove( int from_x, int from_y, int to_x, int to_y );
  Piece* getPiece( int x, int y );
  void goBackAMove();
  void print();
  bool isMate( PieceColor color );
};
