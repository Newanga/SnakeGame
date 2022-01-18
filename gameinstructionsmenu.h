#ifndef GAMEINSTRUCTIONSMENU_H
#define GAMEINSTRUCTIONSMENU_H

#include <QDialog>

namespace Ui {
class GameInstructionsMenu;
}

/**
GameInstructionsMenu header.
*/
class GameInstructionsMenu : public  QDialog
{
    Q_OBJECT

public:
    explicit GameInstructionsMenu(QWidget *parent = nullptr);
    ~GameInstructionsMenu();

private:
    Ui::GameInstructionsMenu *ui;
};

#endif // GAMEINSTRUCTIONSMENU_H
