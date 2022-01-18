#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QKeyEvent>
#include <QMediaPlayer>
#include <QMediaPlaylist>


namespace Ui {
class GameWindow;
}

/**
GameWindow header.
*/
class GameWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GameWindow(QApplication *app,QWidget *parent = nullptr);
    ~GameWindow();

protected:
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
    void keyPressEvent(QKeyEvent *);

private:
    Ui::GameWindow *ui;


    //Game Assets
    QImage tail;
    QImage head;
    QImage apple;


    //Snake initial body length
    int bodyLength;

    //Player Score
    int score = 0;

    //Snake movement area
    int WINDOW_WIDTH = 1000;
    int WINDOW_HEIGHT = 750;

    //Check snake movement direction
    bool isMovingLeft;
    bool isMovingRight;
    bool isMovingUp;
    bool isMovingDown;

    //Check state of game
    bool isGameActive;
    bool isGameMute;


    //Random coordinates to generate apple
    int RAND_POS_X = 39;
    int RAND_POS_Y = 29;

    //Timer
    int timer;

    //Constants
    static const int DELAY = 140;
    static const int DOT_SIZE = 25;
    static const int DOTS = 900;

    //X coordinates of Apple
    int apple_coord_x;
    //Y coordinates of Apple
    int apple_coord_y;

    //Arrays to store all X coordinates of snake body
    int x[DOTS];

    //Arrays to store all Y coordinates of snake body
    int y[DOTS];


    //Game functions
    void loadImages();
    void loadSounds();
    void initStates();
    void initGame();
    void playSound(QString sound);
    void renderApple();
    void checkApple();
    void checkCollision();
    void renderSnakeMovement();
    void renderScreen();
    void gameOver();
    void hideScore();
    void showScore();
    void restart();

    //Sound objects
    QMediaPlayer *mainMusic;
    QMediaPlayer *otherSound;
    QMediaPlaylist *playlist;

    //Main app instance
    QApplication *app;


};



#endif // GAMEWINDOW_H
