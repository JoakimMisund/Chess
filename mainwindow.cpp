#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QPalette>
#include <QColor>
#include <QIcon>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent)
{
  p1 = p2 = NULL;

  QWidget *mainWindow = new QWidget();
  QGridLayout *gridLayout = new QGridLayout();
  gridLayout->setVerticalSpacing(0);
  gridLayout->setHorizontalSpacing(0);
  
  for( int i = 0; i < 8; ++i ) {
    for( int j = 0; j < 8; ++j ) {
      
      QPushButton *label = new QPushButton( QString::fromStdString( " " ) );
      QObject::connect( label, SIGNAL( clicked() ), this , SLOT( handleSquarePress() ) );
      label->setFixedSize( 70, 70 );

      
      if( (i + j) % 2 == 0 ) {
	label->setStyleSheet( "QPushButton{ background:white}" );
      } else {
	label->setStyleSheet( "QPushButton{ background:grey}");
      }
      gridLayout->addWidget( label, i, j );
      buttons[i][j] = label;
    }
  }
  mainWindow->setLayout( gridLayout );
  setCentralWidget( mainWindow );
  setWindowTitle( "Chess" );
  show();
}

MainWindow::~MainWindow()
{
  
}

void MainWindow::showBoard( ) {
  for( int i = 0; i < 8; ++i ) {
    for( int j = 0; j < 8; ++j ) {
      Piece* p = b->getPiece(j,i); 
      QPushButton* label = buttons[i][j];
      if( p != NULL ) {
	
	label->setIcon( getQIcon( p ) );
	label->setIconSize( QSize(60,60) );
      } else {
	label->setIcon( QIcon() );
      }
    }
  }
  update();
}

void MainWindow::setController( Controller *c ) {
  controller = c;
}

void MainWindow::handleSquarePress() {

  QPushButton* pressed = ((QPushButton*)sender());
  Pair *squareClicked = findIndexesOfButton( pressed );
  
  if( p1 == NULL ) {
    
    p1 = squareClicked;
      

  } else if( squareClicked != NULL) {
    controller->moveMade( p1->x, p1->y, squareClicked->x, squareClicked->y );
    p1 = NULL;
  }

}

Pair* MainWindow::findIndexesOfButton( QPushButton* button ) {

  Pair *p = new Pair();

  for( int i = 0; i < 8; ++i ) {
    for( int j = 0; j < 8; ++j ) {
      if( buttons[i][j] == button ) {
	p->x = j;
	p->y = i;
      
      }
    }
  }
  return p;
}

std::string MainWindow::getImageUrl( PieceType p, PieceColor c ) {
  
  if( c == WHITE ) {
    switch( p ) {
    case PAWN: return ":/pieces/pawn_white.png";
    case BISHOP: return ":/pieces/bishop_white.png";
    case KNIGHT: return ":/pieces/knight.png";
    case KING: return ":/pieces/king_white.png";
    case QUEEN: return ":/pieces/queen_white.png";
    case ROOK: return ":/pieces/rook_white.png";
    }
  } else {
   switch( p ) {
    case PAWN: return ":/pieces/pawn_black.png";
    case BISHOP: return ":/pieces/bishop_black.png";
    case KNIGHT: return ":/pieces/knight_black.png";
    case KING: return ":/pieces/king_black.png";
    case QUEEN: return ":/pieces/queen_black.png";
    case ROOK: return ":/pieces/rook_black.png";
    }
  }
  std::cout << (p == PAWN) << " k: " << (c == BLACK) << "\n";
  return "";
}

QIcon MainWindow::getQIcon( Piece* p ) {
  std::string filePath = getImageUrl( p->type, p->color );
  
  QPixmap image(  QString::fromStdString( filePath ) );
  QPixmap scaled = image.scaled( QSize( 60,60 ), Qt::KeepAspectRatio );
  return QIcon(scaled);
}
