#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <quitwidget.h>
#include<QWidget>
#include <mainwindow.h>
#include<QPaintEvent>
#include<QKeyEvent>
#include<QTimer>
#include<QProgressBar>
#include <QVBoxLayout>
#include <cstdlib>
#include <ctime>

class GameBoard : public QWidget
{
    Q_OBJECT
public:
    explicit GameBoard(QWidget *parent = 0);
    ~GameBoard();// destructor
    void init();
    int randnum();

    //================
    void setQuitWidget(QuitWidget* quit_widget);
    void setMainWindow(MainWindow* main_window);
    void paintEvent(QPaintEvent* );
    void keyPressEvent(QKeyEvent *keyevent);

    // functions that control the direction
    void go_up();
    void go_down();
    void go_left();
    void go_right();
    void initialsnake();
    void snaketouchitself();

public slots:
    void auto_run();

private:
    Result result;
    Direct direction;
    QuitWidget* qwidget;
    MainWindow* mw;
    int board_size;

    // snake
    int snake[100][2];
    int food[2];
    int length;
    QTimer *timer;
    int count;
    int level;
    int speed;
    int randcount;
    bool evenodd;
    QProgressBar *progress;

};


#endif // GAMEBOARD_H
