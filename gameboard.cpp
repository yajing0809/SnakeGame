#include "gameboard.h"
#include "ui_gameboard.h"
#include <QtGui>
#define Boardsize 20
/*
 destructor
 */
GameBoard::~GameBoard()
{

}

// set quit widget
void GameBoard::setQuitWidget(QuitWidget* quit_widget) {

    qwidget = quit_widget;
}

// setmainwindow
void GameBoard::setMainWindow(MainWindow* main_window) {
    mw = main_window;

}

// constructor
GameBoard::GameBoard(QWidget *parent) :
    QWidget(parent)
{
    level=1;
    speed=200;
    init();// initial condition
    setWindowTitle("Xenia's Snake Game");
    timer=new QTimer;
    timer->start(speed);
    connect(timer,SIGNAL(timeout()),this,SLOT(auto_run()));
    setFixedSize(360,410);
    progress=new QProgressBar;
    progress->setRange(0,Boardsize);
    progress->setValue(count);
    progress->setOrientation(Qt::Horizontal);
    QVBoxLayout *main=new QVBoxLayout;
    main->addStretch(2);
    main->addWidget(progress);
    setLayout(main);
}

void GameBoard::init()
{
    count=0;
    length=4;
    randcount=0;
    evenodd=0;
    direction=Up;
    result=Ready;

    // the snake body
    snake[0][0]=20*1;
    snake[0][1]=20*13;
    snake[1][0]=20*1;
    snake[1][1]=20*14;
    snake[2][0]=20*1;
    snake[2][1]=20*15;
    snake[3][0]=20*1;
    snake[3][1]=20*16;

    // the food
    food[0]=(randnum()+1)*20;
    food[1]=(randnum()+1)*20;
        for(int i=0;i<length;++i)
        {
            if(level%2)// level 1
            {
                if((food[0]-snake[i][0]==0)
                    &&(food[1]-snake[i][1]==0))
                {
                    food[0]=(randnum()+1)*20;
                    food[1]=(randnum()+1)*20;
                    i=-1;
                    continue;
                }
            }
            else// for level 2
            {
                if(((food[0]==snake[i][0])&&(food[1]==snake[i][1]))
                        ||((food[0]==5*20)&&(food[1]>=7*20)&&(food[1]<=10*20))
                        ||((food[1]==5*20)&&(food[0]>=7*20)&&(food[0]<=10*20)))
                {
                    food[0]=(randnum()+1)*20;
                    food[1]=(randnum()+1)*20;
                    i=-1;
                    continue;
                }
            }
        }
}

// get random number
int GameBoard::randnum()
{
    srand (time(0));
    return rand()%16;//0~15
}

// paint events for snake game
void GameBoard::paintEvent(QPaintEvent* )
{
    QPainter p(this);
    // paint the border and inter
        QRectF border(0,0,16*20+40,16*20+40);
        QRectF inter(20,20,16*20,16*20);
        p.setPen(Qt::NoPen);

    if(level%2)// for level 1
    {
        p.setBrush(QBrush(Qt::darkGreen,Qt::SolidPattern));
    }
    else// for level2
    {
        p.setBrush(QBrush(QColor(0, 0, 255, 127),Qt::SolidPattern));
    }
        p.drawRect(border);
        p.setBrush(QBrush(Qt::lightGray,Qt::SolidPattern));
        p.drawRect(inter);
        p.setPen(QPen(Qt::darkGray,1,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
        p.setBrush(QBrush(QColor(255, 0, 0, 127)));
        QRectF snakehead(snake[0][0],snake[0][1],20,20);
        p.drawEllipse(snakehead);
        QRectF snakefood(food[0],food[1],20,20);
        p.setBrush(QBrush(QColor(255,255, 0, 127)));
        p.drawRoundRect(snakefood);

        // paint the snake
        for(int i=1;i<length;++i)
        {
            QRectF snakebody(snake[i][0],snake[i][1],20,20);
            p.setBrush(QBrush(QColor(255, 0, 0, 127)));
            p.drawEllipse(snakebody);
        }

        QRectF levelinfo(12*20,20,80,20);
        if(level%2)// for level 1
        {
            p.setPen(QPen(Qt::darkGreen));
        }
        else// for level 2
        {
            p.setPen(QPen(QColor(0, 0, 255, 127)));
        }

        QString strlevel="level ";
        int temp;
        if (level%2)
        {
            temp = 1;
        }
        else
        {
            temp = 2;
        }
        if (level == 3)
        {
            p.setFont(QFont("",16,16));
            p.setPen(QPen(QColor(255, 255, 0, 127),60));
            QRectF text(50,50,16*20-50,16*20-50);
            p.drawText(text,"WIN!!");
        }

        QString numlevel=QString::number(temp,10);
        strlevel.append(numlevel);
        p.drawText(levelinfo,Qt::AlignRight,strlevel);

    if(!(level%2))// level 2
    {
        // for the blocks in the middle
        QRectF block1(5*20,7*20,20,4*20);
        p.setBrush(QBrush(QColor(0, 0, 255, 127)));
        p.drawRect(block1);

        QRectF block3(12*20,7*20,20,4*20);
        p.setBrush(QBrush(QColor(0, 0, 255, 127)));
        p.drawRect(block3);

        // for the blocks on the borders
        QRectF block_border1(0,8*20,20,40);
        p.setBrush(QBrush(Qt::lightGray));
        p.drawRect(block_border1);
        QRectF block_border2(17*20,8*20,20,40);
        p.setBrush(QBrush(Qt::lightGray));
        p.drawRect(block_border2);
        QRectF block_border3(8*20,0,40,20);
        p.setBrush(QBrush(Qt::lightGray));
        p.drawRect(block_border3);
        QRectF block_border4(8*20,17*20,40,20);
        p.setBrush(QBrush(Qt::lightGray));
        p.drawRect(block_border4);
    }
    if(result==Ready&& (level!= 3))
    {
        p.setFont(QFont("",16,16));
        p.setPen(QPen(QColor(255, 255, 0, 127),60));
        QRectF text(50,50,16*20-50,16*20-50);
        p.drawText(text,"Ready?\nPress Space start");
    }
    if(result==Lose)
    {
            p.setFont(QFont("",16,16));
            p.setPen(QPen(QColor(255, 255, 0, 127),60));
            QRectF text(50,50,16*20-50,16*20-50);
            p.drawText(text,"LOSE!!\nPress Space restart");
    }
    if(result==Win)
    {
        p.setFont(QFont("",16,16));
        p.setPen(QPen(QColor(255, 255, 0, 127),60));
        QRectF text(50,50,16*20-50,16*20-50);
        p.drawText(text,"WIN!!");
    }
    if((result==Normal)&&(evenodd))
    {
        p.setFont(QFont("",16,16));
        p.setPen(QPen(QColor(255, 255, 0, 127),60));
        QRectF text(50,50,16*20-50,16*20-50);
        p.drawText(text,"Pause");
    }
}

void GameBoard::keyPressEvent(QKeyEvent* keyevent)
{
    switch(keyevent->key())
    {

        case Qt::Key_Down:
            direction=Down;
            break;
        case Qt::Key_Left:
            direction=Left;
            break;
        case Qt::Key_Right:
            direction=Right;
            break;
        case Qt::Key_Up:
        direction=Up;
        break;
        case Qt::Key_Space:
            if(result==Ready)//start
            {
                result=Normal;
                break;
            }
            if(result==Lose)//restart
            {
                init();
                progress->setValue(count);
                update();
                break;
            }
            if(result==Normal)//pause
            {
                if(!evenodd)
                {
                    timer->stop();
                    evenodd=1;
                }
                else
                {
                    timer->start();
                    evenodd=0;
                }
                update();
                break;
            }
           case Qt::Key_P:
        {
        QMutex mut;
        mut.lock();
        mut.tryLock(3000);
        mut.unlock();
        break;
        }
    case Qt::Key_Z:
    {
      speed = speed + 50;
        break;
    }
    case Qt::Key_X:
    {
      speed = speed - 50;
        break;
    }
    }
}

// let the snake run automatically
void GameBoard::auto_run()
{
if(result==Normal)
{
    int temp[2];
    temp[0]=snake[length-1][0];
    temp[1]=snake[length-1][1];
    for(int i=length-1;i>0;--i)
    {
        snake[i][0]=snake[i-1][0];
        snake[i][1]=snake[i-1][1];
    }
    if(direction==Up)
    {
        go_up();
    }
    if(direction==Down)
    {
        go_down();
    }
    if(direction==Left)
    {
        go_left();
    }
    if(direction==Right)
    {
        go_right();
    }
    snaketouchitself();
    if(!(level%2))// level2
    {
        if((snake[0][0]==5*20)
            &&(snake[0][1]>=7*20)
                    &&(snake[0][1]<=10*20))
        {
            result=Lose;
        }
        if((snake[0][0]==12*20)
            &&(snake[0][1]>=7*20)
                    &&(snake[0][1]<=10*20))
        {
            result=Lose;
        }
    }

    // condition where the snake eats the food
    if((snake[0][0]==food[0])&&(snake[0][1]==food[1]))
    {
        count++;
        progress->setValue(count);
        length++;
        snake[length-1][0]=temp[0];
        snake[length-1][1]=temp[1];
        food[0]=(randnum()+1)*20;
        food[1]=(randnum()+1)*20;
        for(int i=0;i<length;++i)
        {
            if(level%2)
            {
                if((food[0]-snake[i][0]==0)\
                        &&(food[1]-snake[i][1]==0))
                {
                    food[0]=(randnum()+1)*20;
                    food[1]=(randnum()+1)*20;
                    i=-1;
                    continue;
                }
            }
            else// level 2
            {
                if(((food[0]==snake[i][0])&&(food[1]==snake[i][1]))
                        ||((food[0]==5*20)&&(food[1]>=7*20)&&(food[1]<=10*20))
                        //||((food[0]==12*20)&&(food[1]>=7*20)&&(food[1]<=10*20))
                        ||((food[1]==5*20)&&(food[0]>=7*20)&&(food[0]<=10*20)))
                        //||((food[1]==12*20)&&(food[0]>=7*20)&&(food[0]<=10*20)))
                {
                    food[0]=(randnum()+1)*20;
                    food[1]=(randnum()+1)*20;
                    i=-1;
                    continue;
                }
            }
        }
        // condition where
        if(count>=Boardsize)
        {
            level++;
            if(level%2)
              speed=speed-50;
            if (level == 3)
            {
                result = Win;
            }
            if(speed<=0)
                speed=20;
            timer->start(speed);
            init();
            progress->setValue(count);
        }
    }
    update();
}
}

void GameBoard ::go_up()
{
    snake[0][1]-=20;
    if(snake[0][1]==snake[2][1])
    {
        snake[0][1]+=40;
    }
    if(snake[0][1]<20||snake[0][1]>16*20)
    {
        if(level%2)//level1
            {
            result=Lose;
            }
        else// level 2
        {
            if(((snake[0][0]==8*20)
                        ||(snake[0][0]==9*20))
                        &&(snake[0][1]==0))
            {
                snake[0][1]=16*20;
            }
            else if(((snake[0][0]==8*20)
                        ||(snake[0][0]==9*20))
                    &&(snake[0][1]==17*20))
            {
                snake[0][1]=20;
            }
            else
            {
                result=Lose;
            }
        }
    }
}

void GameBoard ::go_down()
{
    snake[0][1]+=20;
    if(snake[0][1]==snake[2][1])
    {
        snake[0][1]-=40;
    }
    // condition where the snake touches the wall
    if(snake[0][1]<20||snake[0][1]>16*20)
    {
        if(level%2) // level one
            result=Lose;
        else// level two, two walls in the middle
        {
            if(((snake[0][0]==8*20)
                        ||(snake[0][0]==9*20))
                        &&(snake[0][1]==0))
            {
                snake[0][1]=16*20;
            }
            else if(((snake[0][0]==8*20)
                        ||(snake[0][0]==9*20))
                    &&(snake[0][1]==17*20))
            {
                snake[0][1]=20;
            }
            else
            {
                result=Lose;
            }
        }
    }
}

void GameBoard :: go_left()
{

    snake[0][0]-=20;
    if(snake[0][0]==snake[2][0])
    {
        snake[0][0]+=40;
    }
    // when the snake touches the wall
    if(snake[0][0]<20||snake[0][0]>16*20)
    {
        if(level%2) // level one
            result=Lose;
        else
        {// level two, for two walls in the middle
            if(((snake[0][1]==8*20)
                        ||(snake[0][1]==9*20))
                    &&(snake[0][0]==0))
            {
                snake[0][0]=16*20;
            }
            else if(((snake[0][1]==8*20)
                        ||(snake[0][1]==9*20))
                    &&(snake[0][0]==17*20))
            {
                snake[0][0]=20;
            }
            else
                result=Lose;
        }
    }
}

void GameBoard :: go_right()
{
    snake[0][0]+=20;
    if(snake[0][0]==snake[2][0])
    {
        snake[0][0]-=40;
    }
    // when the snake touches the wall
    if(snake[0][0]<20||snake[0][0]>16*20)
    {
        if(level%2)
            result=Lose;
        else
        {// for level two, when the snake touches the walls in the middle
            if(((snake[0][1]==8*20)
                        ||(snake[0][1]==9*20))
                    &&(snake[0][0]==0))
            {
                snake[0][0]=16*20;
            }
            else if(((snake[0][1]==8*20)
                        ||(snake[0][1]==9*20))
                    &&(snake[0][0]==17*20))
            {
                snake[0][0]=20;
            }
            else
                result=Lose;
        }
    }
}

void GameBoard ::snaketouchitself()
{
    for(int i=1;i<length;++i)
    {
        if((snake[0][0]-snake[i][0]==0)\
                &&(snake[0][1]-snake[i][1]==0))
        {
            result=Lose;
        }
    }
}
