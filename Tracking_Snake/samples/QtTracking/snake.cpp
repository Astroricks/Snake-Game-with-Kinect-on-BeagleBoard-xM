#include<QPainter>
#include<QFrame>
#include<QTime>
#include<QTimer>
#include<QKeyEvent>
#include<QMessageBox>
#include<QLCDNumber>
#include<QLabel>
#include<QPushButton>
#include<QRadialGradient>
#include<QSound>
#include"snake.h"
#include"Tracking.h"

extern unsigned int dir, pre_x, pre_y;
int seq_x[2] = {0, 0}, seq_y[2] = {0, 0};
unsigned int i;

Snake::Snake(QWidget *parent)
    :   QWidget(parent),step(30)
{
    setFocusPolicy(Qt::StrongFocus);
    setFixedSize(1024,768);
    qsrand(QTime(0,0,0).msecsTo(QTime::currentTime()));
    map_row=Height/step;
    map_col=Width/step;
    CanGoThroughWall=false;
    iniWidget();
    iniConnect();
    iniGame();
}

void Snake::iniWidget()
{
    scoreNumber = new QLCDNumber(5);
    scoreNumber->setSegmentStyle(QLCDNumber::Flat);
    scoreNumber->setParent(this);
    scoreNumber->setGeometry(900,30,70,50);

    scoreLabel = new QLabel(this);
    scoreLabel->setFont(QFont("Times",10));
    scoreLabel->setText("Score:");
    scoreLabel->setGeometry(850,40,30,30);

    levelNumber = new QLCDNumber(5);
    levelNumber->setSegmentStyle(QLCDNumber::Flat);
    levelNumber->setParent(this);
    levelNumber->setGeometry(900,90,70,50);

    levelLabel = new QLabel(this);
    levelLabel->setFont(QFont("Times",10));
    levelLabel->setText("Level:");
    levelLabel->setGeometry(850,100,30,30);

    setlabel = new QLabel(this);
    setlabel->setFrameStyle(QFrame::Sunken | QFrame::Panel);
    setlabel->setGeometry(850,150,115,90);
    setlabel->setAlignment(Qt::AlignCenter);
    setlabel->setFont(QFont("Times",10,QFont::Black));
    setlabel->setText(tr("Wall-Cross Denied"));

    button = new QPushButton(this);
    button->setText(tr("Settings"));
    button->setFont(QFont("Times",10));
    button->setGeometry(850,250,100,50);
    button->setFocusPolicy(Qt::NoFocus);

    QLabel* shortKeylabel = new QLabel(this);
    shortKeylabel->setText(tr("Press P to Pause; Move your hand to control"));
    shortKeylabel->setGeometry(60,700,300,19);

    label = new QLabel(this);
    label->setGeometry(5,5,610,610);
    label->setLineWidth(2);
    label->setFrameStyle(QFrame::Box | QFrame::Raised);
}

void Snake::iniConnect()
{//Signal connection
    timer = new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(doMoveSnake()));
    connect(button,SIGNAL(clicked()),this,SLOT(setEnableGoThroughWall()));
}

void Snake::iniGame()
{//Initialize game
    speed=200;
    eatNum=10;
    score=level=0;
    scoreNumber->display(score);levelNumber->display(level);
    timer->stop();
    hasMoved=true;
    header_Index=Max-2;  tail_Index=Max-1;
    tempx=SnakeBody[header_Index][0]=qrand()%map_col;
    tempy=SnakeBody[header_Index][1]=qrand()%map_row;
    eat_X=qrand()%(map_col);
    eat_Y=qrand()%(map_row);
    Dir=-1;
}

void Snake::doMoveSnake()
{//Move the snack by 1 step
    hasMoved=true;
    QString str_x = QString::number(pre_x);
    QString str_y = QString::number(pre_y);
    QString position = str_x + "," + str_y;

    setlabel->setText(position);

    //Sequence 0 is the present coordinate value and sequence 1 is the last coordinate value
    seq_x[1] = seq_x[0];
    seq_y[1] = seq_y[0];
    seq_x[0] = pre_x;
    seq_y[0] = pre_y;

    //Decide when to make a turn
    if(seq_x[0] - seq_x[1] > 12 && pre_x > 60)
    {
        //Turn left;
        if(Dir!=2&&Dir!=3)
        {
            Dir=3;
            hasMoved=false;
        }
    }
    else if(seq_x[0] - seq_x[1] < -12 && pre_x < 40)
    {
        //Turn right;
        if(Dir!=2&&Dir!=3)
        {
            Dir=2;
            hasMoved=false;
        }
    }
    else if(seq_y[0] - seq_y[1] < -12 && pre_y < 40)
    {
        //Turn Up
        if(Dir!=0&&Dir!=1)
        {
             Dir=0;
             hasMoved=false;
        }
    }
    else if(seq_y[0] - seq_y[1] > 12 && pre_y > 60)
    {
        //Turn Down
        if(Dir!=0&&Dir!=1)
        {
             Dir=1;
             hasMoved=false;
        }
    }


    if(isGameOver())
    {//Game over
        QMessageBox::information(this,"GameOver","Game is Over");
        iniGame();
    }
    header_Index=(header_Index-1+Max)%Max;
    SnakeBody[header_Index][0]=tempx;
    SnakeBody[header_Index][1]=tempy;
    if(isEating())
    {
        changeScore();
        changeLevel();
        while(true)
        {//Random the position of food, not covered by the snake
            eat_X=qrand()%(map_col);
            eat_Y=qrand()%(map_row);
            int i;
            for(i=header_Index;i!= tail_Index;i=(i+1)%Max)
                if(eat_X==SnakeBody[i][0]&&eat_Y==SnakeBody[i][1])
                    break;
            if(i==tail_Index) break;
        }
    }
    else tail_Index=(tail_Index-1+Max)%Max;
    update();
}

void Snake::setEnableGoThroughWall()
{//Set wall-cross allow or deny
    CanGoThroughWall=!CanGoThroughWall;
    if(this->CanGoThroughWall)
        setlabel->setText(tr("Wall-Cross Allowed"));
    else    setlabel->setText(tr("Wall-Cross Denied"));
}

void Snake::changeScore()
{//Refresh the score
    score+=10;
    scoreNumber->display(score);
}

void Snake::changeLevel()
{//Refresh the level
    if(eatNum*10==score)
    {
        level++;
        speed=200/(1+level*0.3);
        timer->start(speed);
        eatNum+=10;
    }
    levelNumber->display(level);
}

bool Snake::isEating()
{//Food eating
    if(tempx==eat_X&&tempy==eat_Y) return true;
    return false;
}

bool Snake::isGameOver()
{//If the snake hit the wall or itself, game over
    tempx=SnakeBody[header_Index][0];
    tempy=SnakeBody[header_Index][1];
    if(CanGoThroughWall){//Wall-cross allowed
        switch (Dir)
        {
            case 0:tempy=(tempy-1+map_row)%map_row;break;
            case 1:tempy=(tempy+1)%map_row;break;
            case 2:tempx=(tempx+1)%map_col;break;
            case 3:tempx=(tempx-1+map_col)%map_col;break;
        }
    }
    else{//Wall-cross denied
        switch (Dir)
        {
            case 0:tempy=(tempy-1);break;
            case 1:tempy=(tempy+1);break;
            case 2:tempx=(tempx+1);break;
            case 3:tempx=(tempx-1);break;
        }
        if(tempx<0||tempy<0||tempx==map_col||tempy==map_row) return true;//Hit the wall
    }
    int i;
    for(i=header_Index;i!=tail_Index;i=(i+1)%Max)//Hit itself
        if(tempx==SnakeBody[i][0] && tempy==SnakeBody[i][1])  break;
    if(i==tail_Index) return false;
    return true;
}

void Snake::paintEvent(QPaintEvent *event)
{//Paint the screen
    QPainter painter(this);
    QRect rect = QRect(10,10,600,600);
    painter.fillRect(rect,Qt::white);
    //painter.setRenderHint(QPainter::Antialiasing);
    for(int i = header_Index;i != tail_Index;i=(i+1)%Max)//Draw the snake
    {
        int sx=SnakeBody[i][0]*step+10;
        int sy=SnakeBody[i][1]*step+10;
        QBrush brush;QPen pen;
        QColor color =Qt::green;
        painter.setBrush(color);
        painter.drawRect(sx,sy,step,step);

        pen.setColor(color.light(200));
        pen.setWidth(1);
        painter.setPen(pen);
        painter.drawLine(sx,sy,sx,sy+step);
        painter.drawLine(sx,sy+step,sx+step,sy+step);
        painter.drawLine(sx,sy,sx+step,sy);
        painter.drawLine(sx+step,sy,sx+step,sy+step);

    }
    painter.setPen(Qt::NoPen);
    painter.setBrush(getColor());
    if(timer->isActive())//Draw food
        painter.drawRect(eat_X*step+10,eat_Y*step+10,step,step);
}

void Snake::keyPressEvent(QKeyEvent *event)
{//Catch key-press signal
    if(hasMoved){

        if(!timer->isActive()) timer->start(speed);
        switch (event->key())
        {
            case Qt::Key_Up: if(Dir!=0&&Dir!=1){
                                Dir=0;hasMoved=false;
                            }
                            break;
            case Qt::Key_Down:if(Dir!=1&&Dir!=0){
                                Dir=1;hasMoved=false;
                            }
                            break;
            case Qt::Key_Right:if(Dir!=2&&Dir!=3){
                                Dir=2;hasMoved=false;
                            }
                            break;
            case Qt::Key_Left:if(Dir!=2&&Dir!=3){
                            Dir=3;hasMoved=false;
                            }
                            break;
            case Qt::Key_P:timer->stop();break;
            default :
                        if(Dir==-1)
                                Dir=qrand()%4;
        }
    }
}

QColor Snake::getColor()
{//Get random color
    static const QRgb colorTable[8] = {
        0x000000, 0xCC6666, 0x66CC66, 0x6666CC,
        0xCCCC66, 0xCC66CC, 0x66CCCC, 0xDAAA00
    };
    QColor color;
    color = colorTable[qrand()%8];
    return color;
}
