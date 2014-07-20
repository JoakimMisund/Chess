#include "controller.h"

#include <ChessBoard.h>
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QSignalMapper>

#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#endif

class ChessBoard;


struct Pair {
  int x, y;
};

std::string convertPieceToString( Piece* p );


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    void showBoard( );
    void setController( Controller *c );
    ~MainWindow();
    ChessBoard *b;
    

 public slots:
   void handleSquarePress();

 private:
   
   Controller *controller;
   QPushButton *buttons[8][8];
   Pair *p1,*p2;
   Pair* findIndexesOfButton( QPushButton* button );
   std::string getImageUrl( PieceType p, PieceColor c );
   QIcon getQIcon( Piece* p );
};

#endif // MAINWINDOW_H



