#include "about.h"
#include "ui_about.h"

/**
About Constructor.
*/
About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
}

/**
About Destructor.
*/
About::~About()
{
    delete ui;
}
