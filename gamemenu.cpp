#include "gamemenu.h"
#include "ui_gamemenu.h"
#include "gameinstructionsmenu.h"
#include "gamewindow.h"
#include "about.h"
#include <QMediaPlayer>
#include <QMediaPlaylist>

/**
GameMenu Constructor.
*/
GameMenu::GameMenu(QApplication *app ,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameMenu)
{
    ui->setupUi(this);
    this->app=app;

    //Disable resizing of window
    setFixedSize(width(), height());

    //Start playing music when displaying the game menu
    playMusic();
}

/**
GameMenu Destructor.
*/
GameMenu::~GameMenu()
{
    delete ui;
}

/**
Start playing Game menu music.
*/
void GameMenu::playMusic()
{
    playlist = new QMediaPlaylist();
    music = new QMediaPlayer();
    playlist->addMedia(QUrl("qrc:/Sounds/Resources/Sounds/game_menu_music.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    music->setPlaylist(playlist);
    music->play();
}

/**
Mute Game menu music.
*/
void GameMenu::muteMusic()
{
    music->setMuted(true);
}

/**
Unmute Game menu music.
*/
void GameMenu::unmuteMusic()
{
    music->setMuted(false);
}



/**
Load About window when button is clicked.
*/
void GameMenu::on_aboutBtn_clicked()
{
    about=new About();
    about->setFixedSize(321,391);
    about->setWindowIcon(QIcon(":/Icons/Resources/Icons/Icon.ico"));
    about->setWindowTitle("About");
    about->exec();
}

/**
Load game instructions window when button is clicked.
*/
void GameMenu::on_howBtn_clicked()
{
    instructions=new GameInstructionsMenu();
    instructions->setFixedSize(385,442);
    instructions->setWindowIcon(QIcon(":/Icons/Resources/Icons/Icon.ico"));
    instructions->setWindowTitle("How to Play");
    instructions->exec();
}


/**
Start game when button is clicked.
*/
void GameMenu::on_startBtn_clicked()
{
    muteMusic();
    this->hide();
    game=new GameWindow(this->app);
    game->setWindowTitle("Game");
    game->setWindowIcon(QIcon(":/Icons/Resources/Icons/Icon.ico"));
    game->setFixedSize(1000,750);
    game->show();
}

/**
Exit game when button is clicked.
*/
void GameMenu::on_exitBtn_clicked()
{
    app->exit();
}


/**
Control Menu Sound
*/
void GameMenu::on_soundBtn_clicked(){
    soundControl();
}

/**
Adjust Menu Sound
*/
void GameMenu::soundControl(){
    if(music->isMuted()==false){
        music->setMuted(true);
        ui->soundBtn->setStyleSheet("background-color:transparent;background-image: url(:/Images/Resources/Images/unmute.png);background-repeat:none;");
    }
    else{
        music->setMuted(false);
        ui->soundBtn->setStyleSheet("background-color:transparent;background-image: url(:/Images/Resources/Images/mute.png);background-repeat:none;");
    }
}

/**
Control Menu keyboard events
*/
void GameMenu::keyPressEvent(QKeyEvent *e) {

    int key = e->key();

    if (key == Qt::Key_M) {
        soundControl();
    }

    QWidget::keyPressEvent(e);
}

