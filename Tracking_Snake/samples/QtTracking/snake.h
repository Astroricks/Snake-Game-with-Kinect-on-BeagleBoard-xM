#ifndef SNAKE_H
#define SNAKE_H
#include<QWidget>
#define Max 200
#define Width 600
#define Height 600
class QLabel;
class QTimer;
class QLCDNumber;
class QPushButton;
class QTime;
class QDate;

class Snake : public QWidget
{
    Q_OBJECT
public:
    Snake(QWidget* = 0);
private:
    char    SnakeBody[Max][2];              //Coordinate position of the snake body
    int     header_Index,tail_Index;       //Head, tail index in the array
    int     eat_X,eat_Y;                  //Food position
    int     level;                       //Level
    int     speed;                      //Speed
    int     score,eatNum;              //Score
    int     map_row,map_col;          //Size of map
    int     Dir;                     //Moving direction
    int     step;
    int     tempx,tempy;           //Next position of head
    bool    CanGoThroughWall;     //Wall cross set
    bool    hasMoved;            //Avoid the error for too small key press time interval
    QLCDNumber* levelNumber;
    QLCDNumber* scoreNumber;
    QLabel*     label;
    QLabel*     levelLabel;
    QLabel*     scoreLabel;
    QLabel*     setlabel;
    QTimer*     timer;
    QTimer*     GameTimer;
    QPushButton*    button;

    void    iniWidget();
    void    initSnakeBody();
    void    iniConnect();
    bool    isEating();
    bool    isGameOver();
    void    iniGame();
    void    changeScore();
    void    changeLevel();
    QColor  getColor();
private slots:
    void    doMoveSnake();
    void    setEnableGoThroughWall();
protected:
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *event);
};

#endif // SNAKE_H
