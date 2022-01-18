#include <QPainter>
#include <QTime>
#include <QTimer>
#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "gamemenu.h"
#include <QDebug>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QMessageBox>
#include <QAbstractButton>


/**
GameWindow Constructor.
*/
GameWindow::GameWindow(QApplication *app ,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    this->app=app;
    initStates();
    loadImages();
    loadSounds();
    initGame();

}


/**
GameWindow Destructor.
*/
GameWindow::~GameWindow()
{
    delete ui;
}

/**
Load required game images at start.
*/
void GameWindow::loadImages() {
    tail.load(":/Images/Resources/Images/tail.png");
    head.load(":/Images/Resources/Images/head.png");
    apple.load(":/Images/Resources/Images/apple.png");
}

/**
Load required game sounds at start.
*/
void GameWindow::loadSounds() {
    otherSound = new QMediaPlayer();
    playlist = new QMediaPlaylist();
    mainMusic = new QMediaPlayer();
    playlist->addMedia(QUrl("qrc:/Sounds/Resources/Sounds/snake_hiss.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    mainMusic->setPlaylist(playlist);
    mainMusic->play();
}

/**
Initialize Game variables at start.
*/
void GameWindow::initStates() {
    isMovingLeft = false;
    isMovingRight = true;
    isMovingUp = false;
    isMovingDown = false;
    isGameActive = true;
    isGameMute=false;
}


/**
Initialize game start.
*/
void GameWindow::initGame() {

    bodyLength = 3;

    for (int i = 0; i < bodyLength; i++) {
        x[i] = 50 - i * 10;
        y[i] = 50;
    }

    showScore();
    renderApple();

    timer = startTimer(DELAY);
}

/**
Randomly render a apple on screen
*/
void GameWindow::renderApple() {
    QTime time = QTime::currentTime();
    qsrand((uint) time.msec());

    int r = qrand() % RAND_POS_X;
    apple_coord_x = (r * DOT_SIZE);

    r = qrand() % RAND_POS_Y;
    apple_coord_y = (r * DOT_SIZE);
}


/**
Paint the screen based on state of game
*/
void GameWindow::paintEvent(QPaintEvent *e) {

    Q_UNUSED(e);

    renderScreen();
}

/**
Start to paint screen after state change
*/
void GameWindow::renderScreen() {

    QPainter painter(this);

    if (isGameActive) {
        painter.drawImage(apple_coord_x, apple_coord_y, apple);
        for (int i = 0; i < bodyLength; i++) {
            if (i == 0) {
                painter.drawImage(x[i], y[i], head);
            } else {
                painter.drawImage(x[i], y[i], tail);
            }
        }
        showScore();

    } else {
        hideScore();
//        gameOver(painter);
        gameOver();
    }
}

/**
Actions when game is over
*/
void GameWindow::gameOver() {

    mainMusic->stop();
    otherSound->stop();
    this->setUpdatesEnabled(false);

    QMessageBox msgBox;
    QString score = "Your Score is " + ui->scoreValueLbl->text();
    msgBox.setStyleSheet("QLabel{min-width: 400px;font-size:46;}");
    msgBox.setText("<font size = 6 >" +score + "</font> ");
    msgBox.setWindowTitle("Game Over");
    msgBox.setInformativeText("<font size = 4 > Do You want to play Again? </font> ");
    msgBox.setStandardButtons(QMessageBox::Retry | QMessageBox::Close );
    msgBox.setDefaultButton(QMessageBox::Retry);
    int ret = msgBox.exec();

    switch (ret) {
      case QMessageBox::Retry:
          this->setUpdatesEnabled(true);
          restart();
          break;
      case QMessageBox::Close:
          this->close();
          break;
      default:
          break;
    }

}


/**
Action after an apple is eaten by the snake.
*/
void GameWindow::checkApple() {

    QString str;
    if ((x[0] == apple_coord_x) && (y[0] == apple_coord_y)) {
        ++score;
        bodyLength++;
        ui->scoreValueLbl->setText(str.number(score));
        playSound("eat");
        renderApple();
    }
}

/**
Help paint event to render snake movements on screen
*/
void GameWindow::renderSnakeMovement() {

    for (int i = bodyLength; i > 0; i--) {
        x[i] = x[(i - 1)];
        y[i] = y[(i - 1)];
    }

    if (isMovingLeft) {
        x[0] -= DOT_SIZE;
    }

    if (isMovingRight) {
        x[0] += DOT_SIZE;
    }

    if (isMovingUp) {
        y[0] -= DOT_SIZE;
    }

    if (isMovingDown) {
        y[0] += DOT_SIZE;
    }
}
/**
Check for snake collison with tail or with the wall.
*/
void GameWindow::checkCollision() {

    for (int i = bodyLength; i > 0; i--) {

        if ((i > 4) && (x[0] == x[i]) && (y[0] == y[i])) {
            playSound("death");
            isGameActive = false;
        }
    }

    if (y[0] >= WINDOW_HEIGHT) {
        isGameActive = false;
    }

    if (y[0] < 0) {
        isGameActive = false;
    }

    if (x[0] >= WINDOW_WIDTH) {
        isGameActive = false;
    }

    if (x[0] < 0) {
        isGameActive = false;
    }

    if(!isGameActive) {
        killTimer(timer);
    }
}


/**
Timer to refresh and paint screen
*/
void GameWindow::timerEvent(QTimerEvent *e) {
    Q_UNUSED(e);

    if (isGameActive) {
        WINDOW_HEIGHT = this->height();
        WINDOW_WIDTH = this->width();
        RAND_POS_X = WINDOW_WIDTH / DOT_SIZE - 1;
        RAND_POS_Y = WINDOW_HEIGHT / DOT_SIZE - 1;
        checkApple();
        checkCollision();
        renderSnakeMovement();
    }
    repaint();
}

/**
Hide score after game is over
*/
void GameWindow::hideScore(){
    ui->scoreLbl->hide();
    ui->scoreValueLbl->hide();
}

/**
Show score when starting new game
*/
void GameWindow::showScore(){
    ui->scoreLbl->show();
    ui->scoreValueLbl->show();
}

/**
Response to keyboard events from user
*/
void GameWindow::keyPressEvent(QKeyEvent *e) {

    int key = e->key();

    if ((key == Qt::Key_Up) && (!isMovingDown)) {
        isMovingUp = true;
        isMovingRight = false;
        isMovingLeft = false;
    }

    if ((key == Qt::Key_Down) && (!isMovingUp)) {
        isMovingDown = true;
        isMovingRight = false;
        isMovingLeft = false;
    }

    if ((key == Qt::Key_Left) && (!isMovingRight)) {
        isMovingLeft = true;
        isMovingUp = false;
        isMovingDown = false;
    }

    if ((key == Qt::Key_Right) && (!isMovingLeft)) {
        isMovingRight = true;
        isMovingUp = false;
        isMovingDown = false;
    }

    if (key == Qt::Key_M && isGameActive) {
        if(mainMusic->isMuted()==false){
            mainMusic->setMuted(true);
            isGameMute=true;
        }
        else{
            mainMusic->setMuted(false);
            isGameMute=false;
        }
    }

    QWidget::keyPressEvent(e);
}

/**
Show score when starting new game
*/
void GameWindow::playSound(QString sound){
    if(!isGameMute && isGameActive){
        if(sound=="eat"){
            otherSound->setMedia(QUrl("qrc:/Sounds/Resources/Sounds/eat_apple.mp3"));
            otherSound->play();
        }
        else if(sound=="death"){
            mainMusic->setMuted(true);
            otherSound->setMedia(QUrl("qrc:/Sounds/Resources/Sounds/snake_death.mp3"));
            otherSound->play();
        }
    }
}


/**
Reinitialize game start to retry.
*/
void GameWindow::restart(){
    isMovingLeft = false;
    isMovingRight = true;
    isMovingUp = false;
    isMovingDown = false;
    isGameActive = true;
    score = 0;
    ui->scoreValueLbl->setText("0");
    initGame();
    loadSounds();
}


