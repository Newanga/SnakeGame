#include "gameinstructionsmenu.h"
#include "ui_gameinstructionsmenu.h"

/**
GameInstructionsMenu Constructor.
*/
GameInstructionsMenu::GameInstructionsMenu(QWidget *parent) :
     QDialog(parent),
    ui(new Ui::GameInstructionsMenu)
{
    ui->setupUi(this);
}

/**
GameInstructionsMenu Destructor.
*/
GameInstructionsMenu::~GameInstructionsMenu()
{
    delete ui;
}
