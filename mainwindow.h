#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QLabel>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTimer>
#include <QPushButton>
#include <iostream>
#include "quitwidget.h"
#include <QRadioButton>
enum Direct
{
    Up,
    Down,
    Left,
    Right
};
enum Result
{
    Win,
    Lose,
    Normal,
    Ready
};
class GameBoard;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void closeEvent(QCloseEvent *e);
    ~MainWindow();
    void setQuitWidget(QuitWidget* quit_widget);
    void setGameBoard(GameBoard* game_board);

private:
    QuitWidget* qwidget;
    GameBoard* board;
    QLabel * gamename;
    QLabel * difficulty;
    QPushButton * start;
    QVBoxLayout * levellayout;
    QVBoxLayout * final_layout;
    QWidget * central;

};

#endif // MAINWINDOW_H
