#-------------------------------------------------
#
# Project created by QtCreator 2014-07-07T17:40:05
#
#-------------------------------------------------

QT       += core gui

TARGET = Chess_qt
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Square.cpp \
    ChessPiece.cpp \
    ChessBoard.cpp \
    controller.cpp

HEADERS  += mainwindow.h \
    Square.h \
    ChessPiece.h \
    ChessBoard.h \
    controller.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    ../../Chess/src/Square.h.gch \
    ../../Chess/src/ChessPiece.h.gch \
    ../../Chess/src/ChessBoard.h.gch

RESOURCES += \
    pieces.qrc
