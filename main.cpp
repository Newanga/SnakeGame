#include "gamemenu.h"

#include <QApplication>
#include <QFontDatabase>


/**
starting function(point) of programe.
*/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameMenu w(&a);
    //Set main window icon
    w.setWindowIcon(QIcon(":/Icons/Resources/Icons/Icon.ico"));
    w.setFixedSize(325,522);
    w.setWindowTitle("Game Menu");
    w.show();
    return a.exec();
}
