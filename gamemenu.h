#ifndef GAMEMENU_H
#define GAMEMENU_H

#include <QMainWindow>
#include "gameinstructionsmenu.h"
#include "gamewindow.h"
#include "about.h"
#include <QMediaPlayer>
#include <QMediaPlaylist>




QT_BEGIN_NAMESPACE
namespace Ui { class GameMenu; }
QT_END_NAMESPACE

/**
GameMenu header.
*/
class GameMenu : public QMainWindow
{
    Q_OBJECT

public:
    GameMenu(QApplication *app, QWidget *parent = nullptr);
    ~GameMenu();

protected:
    void keyPressEvent(QKeyEvent *);

private slots:

    void on_aboutBtn_clicked();

    void on_howBtn_clicked();

    void on_startBtn_clicked();

    void on_exitBtn_clicked();

    void playMusic();

    void muteMusic();

    void unmuteMusic();

    void on_soundBtn_clicked();

    void soundControl();


private:
    Ui::GameMenu *ui;
    QApplication *app;
    GameInstructionsMenu *instructions;
    GameWindow *game;
    About *about;
    QMediaPlayer *music;
    QMediaPlaylist *playlist;


};
#endif // GAMEMENU_H
