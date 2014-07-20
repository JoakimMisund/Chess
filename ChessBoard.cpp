#include "ChessBoard.h"
#include <cstdlib>
#include <iostream>

Move::Move( int fx, int fy, int tx, int ty, Piece* taken ) {

  from_x = fx;
  from_y = fy;
  to_x = tx;
  to_y = ty;
  pieceTaken = taken;
}

Move::Move( int fx, int fy, int tx, int ty ) {

  from_x = fx;
  from_y = fy;
  to_x = tx;
  to_y = ty;
  pieceTaken = NULL;
}


ChessBoard::ChessBoard() {

  initializeBoard();

}

Piece* ChessBoard::getPiece( int x, int y ) {
  if( x > 7 || x < 0 || y > 7 || y < 0 ) return NULL;
  if( &board[y][x] == NULL ) return NULL;
  if( (&board[y][x])->getPiece() == NULL ) return NULL;
  return board[y][x].getPiece();

}

Piece* ChessBoard::removePiece( int x, int y ) {
  return board[y][x].removePiece();
}

void ChessBoard::initializeBoard() {

  for( int i = 0; i < BOARD_WIDTH_HEIGHT; ++i ) {
    for( int j = 0; j < BOARD_WIDTH_HEIGHT; ++j ) {

      PieceColor squareColor;
      if( (i+j) % 2 == 0 ) squareColor = WHITE;
      else squareColor = BLACK;

      Square* sq = &board[i][j];
      sq->color = squareColor;

      if( i < 2 || i > 5 ) {

	PieceColor color;
	if( i < 2 ) color = BLACK;
	else color = WHITE;

	PieceType type;
	if( i == 0 || i == 7 ) type = getPieceType( j );
	else type = PAWN;

	Piece* piece = new Piece( type, color, true );
	piece->x = j;
	piece->y = i;

	sq->setPiece( piece );
	if( i < 2 ) blackPieces.push_back( piece );
	else whitePieces.push_back( piece );

      } else {

	sq->setPiece(NULL);
      }

      sq->x = j;
      sq->y = i;


    }
  }
}

PieceType ChessBoard::getPieceType( int j ) {

  switch(j) {
  case 0: return ROOK;
  case 1: return KNIGHT;
  case 2: return BISHOP;
  case 3: return QUEEN;
  case 4: return KING;
  case 5: return BISHOP;
  case 6: return KNIGHT;
  case 7: return ROOK;
  default: return PAWN;
  }
}


bool ChessBoard::makeMove(int from_x, int from_y, int to_x, int to_y ) {
  Move move( from_x, from_y, to_x, to_y );

  /* the code that validates the move, does not check the position after the move
     this is done in the end of this method */

  if( !validateMove( move ) ) return false;

  if( getPiece( from_x, from_y )->type == KING && std::abs(to_x - from_x) == 2) {
    if( to_x != 2 ) {
      setPiece( from_x + 1, from_y, removePiece(to_x+1, to_y) );
    } else {
      setPiece( from_x - 1, from_y, removePiece(to_x - 2, to_y) );
    }
  }

  /* adds the piece to be taken if exists, then adds the move to the stack of moves */

  Piece* pieceToMove = removePiece( from_x, from_y );
  move.pieceTaken = getPiece( to_x, to_y );

  if( move.pieceTaken != NULL ) {

    if( pieceToMove->color == move.pieceTaken->color) {
      setPiece( from_x, from_y, pieceToMove );

      return false;
    }

    move.pieceTaken->inPlay = false;
  }
  moves.push( move );

  /* retrives the piece that is to be moved, and then it moves it. at the end the new
     position is updaten in the piece-object */
  setPiece( to_x, to_y, pieceToMove );
  pieceToMove->x = to_x;
  pieceToMove->y = to_y;
  PieceColor colorOfMovingPlayer = pieceToMove->color;
  pieceToMove->nrOfMoves++;

  /* checks if the king of the player which just moved is in check,
     if so the move is invalid and it goes back a move */
  if( playersKingInCheck( colorOfMovingPlayer ) ) {

    goBackAMove();
    return false;
  }
  return true;
}

bool ChessBoard::validateMove( Move move ) {

  int from_x = move.from_x, from_y = move.from_y;
  int to_x = move.to_x, to_y = move.to_y;

  //Square* from_square = board[from_y][from_x];
  //Square* to_square = board[to_y][to_x];

  Piece* toMove_piece = getPiece( from_x, from_y );

  //If the square given contains no piece*, the move is invalid
  if( toMove_piece == NULL ){
    return false;
  }

  if( from_x == to_x && from_y == to_y ) {
    return false;
  }

  PieceType type = toMove_piece->type;

  if( type == QUEEN ) {

    return ( checkDiagonalLine( move ) || checkHorisontalOrVerticalLine( move ) );

  } else if( type == BISHOP ) {

    return checkDiagonalLine( move );

  } else if( type == ROOK ) {

    return checkHorisontalOrVerticalLine( move );

  } else if( type == KNIGHT ) {

    return validateKnightMove( move );

  } else if( type == PAWN ) {

    return validatePawnMove( move );

  } else {

    return validateKingMove( move );
  }
}

bool ChessBoard::checkDiagonalLine( Move move ) {

  int dif_x = move.to_x - move.from_x;
  int dif_y = move.to_y - move.from_y;

  if( std::abs(dif_y) != std::abs(dif_x) ) return false;

  int dir_x = dif_x/std::abs( dif_x );
  int dir_y = dif_y/std::abs( dif_y );
  int x = move.from_x + dir_x, y = move.from_y + dir_y;

  while( x != move.to_x && y != move.to_y ) {

    if( getPiece( x, y ) != NULL ) return false;

    x += dir_x;
    y += dir_y;
  }

  return true;
}

bool ChessBoard::checkHorisontalOrVerticalLine( Move move ) {

  int dif_x = move.to_x - move.from_x;
  int dif_y = move.to_y - move.from_y;

  if( dif_x != 0 && dif_y != 0 ) return false;

  int dir_x = 0;
  int dir_y = 0;
  if( dif_x != 0 ) {
    dir_x = dif_x/std::abs( dif_x );
  } else {
    dir_y = dif_y/std::abs( dif_y );
  }

  int x = move.from_x + dir_x, y = move.from_y + dir_y;

  while( x != move.to_x || y != move.to_y ) {

    if( getPiece( x, y ) != NULL ) return false;

    x += dir_x;
    y += dir_y;
  }
  std::cout << (move.from_x + dir_x) << " y: " << (move.from_y + dir_y) << "\n";
  std::cout << (getPiece( (move.from_x + dir_x) , (move.from_y + dir_y) ) != NULL ) << "\n";
  return true;
}

bool ChessBoard::validateKnightMove( Move move ) {

  int dif_x = move.to_x - move.from_x;
  int dif_y = move.to_y - move.from_y;


  if( std::abs(dif_x) == 2 || std::abs(dif_y) == 2 ) {
    if( std::abs(dif_x) == 1 || std::abs(dif_y) == 1 ) {
      return true;
    }
  }

  return false;
}

bool ChessBoard::validateKingMove( Move move ) {

  int dif_x = std::abs( move.to_x - move.from_x );
  int dif_y = std::abs( move.to_y - move.from_y );
  Piece* king = getPiece( move.from_x, move.from_y );

  if( dif_x == 2 && dif_y == 0 ) {
    Piece* rook;
    if( move.to_x != 2 ) {
       rook = getPiece( move.to_x + 1, move.to_y);
      if( rook != NULL && rook->nrOfMoves == 0 && king->nrOfMoves == 0) {
	if( checkHorisontalOrVerticalLine( Move( move.from_x, move.from_y, move.to_x+1, move.to_y) ) ) {
	  return true;
	}
      }
    } else {
      rook = getPiece( move.to_x - 2, move.to_y );
      if( rook != NULL && rook->nrOfMoves == 0 && king->nrOfMoves == 0) {
	if( checkHorisontalOrVerticalLine( Move( move.from_x, move.from_y, move.to_x-2, move.to_y) ) ) {
	  return true;
	}
      }
    }
  }

  return (dif_x <= 1 && dif_y <= 1 );
}


bool ChessBoard::playersKingInCheck( PieceColor playerInMove ) {

  Square* king = findKing( playerInMove );

  int x = king->x;
  int y = king->y;

  PieceColor color;

  if( playerInMove == BLACK )
    color = WHITE;
  else
    color = BLACK;

  return checkIfCanMoveTo( color, x, y );
}

bool ChessBoard::checkIfCanMoveTo( PieceColor color, int to_x, int to_y ) {

  std::vector<Piece*> toCheck;

  if( color == WHITE ) {
    toCheck = whitePieces;
  }
  else {
    toCheck = blackPieces;
  }

  for( std::vector<Piece*>::iterator it = toCheck.begin(); it != toCheck.end(); ++it ) {

    if( (*it)->inPlay ) {

      Move m((*it)->x, (*it)->y, to_x, to_y);

      if( validateMove( m ) ){
	std::cout << ((*it)->x) << " " << ((*it)->y) << "\n";
	return true;
      }
    }
  }

  return false;
}

Square* ChessBoard::findKing( PieceColor color ) {

  for( int i = 0; i < BOARD_WIDTH_HEIGHT; ++i ) {
    for( int j = 0; j < BOARD_WIDTH_HEIGHT; ++j ) {
      Piece* p = getPiece(i,j);
      if( p != NULL ) {
	if( p->type == KING && p->color == color) return getSquare(i,j);
      }
    }
  }
  return NULL;
}

void ChessBoard::goBackAMove() {

  Move prevMove = moves.top();
  moves.pop();

  int from_x = prevMove.from_x;
  int from_y = prevMove.from_y;
  int to_x = prevMove.to_x;
  int to_y = prevMove.to_y;

  Piece* moveBackPiece = removePiece( to_x, to_y );
  moveBackPiece->nrOfMoves--;
  setPiece( from_x, from_y, moveBackPiece );
  moveBackPiece->x = from_x;
  moveBackPiece->y = from_y;

  if( moveBackPiece->type == KING && std::abs(to_x - from_x) == 2 ) {
    if( to_x != 2 ) {
      setPiece( to_x+1, to_y, removePiece( from_x+1, from_y));
    } else {
      setPiece( to_x - 2, to_y, removePiece( from_x-1, from_y));
    }
  }

  Piece* backInPlay = prevMove.pieceTaken;

  if( backInPlay != NULL ) {
    setPiece( to_x, to_y, backInPlay );
    backInPlay->x = to_x;
    backInPlay->y = to_y;
  }
}


bool ChessBoard::validatePawnMove( Move move ) {

  Piece* pawn = getPiece( move.from_x, move.from_y );
  PieceColor pawn_color = pawn->color;
  int dif_x = std::abs( move.to_x - move.from_x );
  int dif_y = std::abs( move.to_y - move.from_y );

  /* check if the pawn is moving the right way*/
  if( !validatePawnVerticalDirection( pawn_color, move.to_y, move.from_y ) ) {
    return false;
  }


  if( dif_y == 2 ) {

    if( move.from_y != 6 && move.from_y != 1 ) return false;
    if( !checkHorisontalOrVerticalLine( move ) ) return false;
    if( getPiece( move.to_x, move.to_y ) != NULL ) return false;
    /* should add ampasang rules */
    
  } else if( dif_y == 1 ) {

    if( dif_x > 1 ) return false;

    if( dif_x == 1 ) {

      std::cout << "before amp\n" <<  move.from_x  << " " << move.from_y << " " << move.to_x  << " " << move.from_x <<" " << dif_x << " " << moves.size() << "\n";
      
      if ( getPiece(move.to_x, move.to_y ) == NULL ) {

	if( moves.size() != 0 ) {
	
	  std::cout << "checking amp\n";

	  Move prevMove = moves.top();

	  Piece* piece = getPiece( prevMove.to_x, prevMove.to_y );
      
	  if( ( piece->type != PAWN) ) {
	    std::cout << "number one\n";
	    return false;
	  }
	  if( std::abs( prevMove.from_y - prevMove.to_y ) != 2 || prevMove.to_x != prevMove.from_x ) {
	    std::cout << "number two\n";
	    return false;
	  }
	  
	  if( std::abs( prevMove.to_y - move.to_y ) > 1 ) return false;
	
	}
      }
      
    } else {
      return ( !(getPiece(move.to_x, move.to_y ) != NULL) );
    }

  } else {

    return false;
  }
  return true;
}


void ChessBoard::setPiece( int x, int y, Piece* piece ) {

  board[y][x].setPiece( piece );
}

bool ChessBoard::validatePawnVerticalDirection( PieceColor color, int to_y, int from_y ) {

  if( color == WHITE ) {

    return ( to_y < from_y );

  } else {

    return ( to_y > from_y );

  }
}

Square* ChessBoard::getSquare( int x, int y ) {

  return &board[y][x];
}

void ChessBoard::print() {
  /*for( int i = 0; i < BOARD_WIDTH_HEIGHT; ++i ) {
    for( int j = 0; j < BOARD_WIDTH_HEIGHT; ++j ) {
    std::cout << (board[i][j] == NULL );
    }
    std::cout << "\n";
    }*/

  std::cout << sizeof(board)/sizeof(board[0]) << "\n";
  std::cout << sizeof( board[0] ) / sizeof( board[0][0] ) << "\n";

  std::cout << ( &board[0][0] == NULL ) << "\n";
}

//TODO
bool ChessBoard::isMate( PieceColor color ) {

  Square* kS = findKing( color );
  Piece* king = kS->getPiece();
  int from_x = kS->x, from_y = kS->y;

  PieceColor toMove;

  if( color == WHITE ) toMove = BLACK;
  else toMove = WHITE;

  int poss[8][2] = {{1,1},{1,0},{0,1},{-1,-1}, {-1,0},{0,-1}, {1,-1},{-1,1}};

  for( int i = 0; i < 8; ++i ) {

    int to_x = from_x + poss[i][0];
    int to_y = from_y + poss[i][1];

    if( to_x < 0 || to_x >=8 || to_y < 0 || to_y >= 8 ) {
      continue;
    } else {
      Piece* toTake = getPiece( to_x, to_y );

      if( checkIfCanMoveTo( toMove, to_x, to_y ) ) {
	continue;
      }

      if( toTake != NULL ) {
	if( toTake->color == color ) {
	  continue;
	}
      }
      return false;
    }
  }
  return true;

  std::vector<Piece*> pieces = findThreatheningPieces( king );
  //To do, check if any of the pieces can take the threathening pieces.
}

std::vector<Piece*> ChessBoard::findThreatheningPieces( Piece* p ) {
  std::vector<Piece*> pieces;

  PieceColor color;

  if (p->color = WHITE) color = BLACK;
  else color = WHITE;

  std::vector<Piece*> toCheck;

  if( color == WHITE ) {
    toCheck = whitePieces;
  }
  else {
    toCheck = blackPieces;
  }

  for( std::vector<Piece*>::iterator it = toCheck.begin(); it != toCheck.end(); ++it ) {

    if( (*it)->inPlay ) {

      Move m((*it)->x, (*it)->y, p->x, p->y);

      if( validateMove( m ) ){
	pieces.push_back( getPiece( (*it)->x, (*it)->y ) );
      }
    }
  }

  return pieces;
}