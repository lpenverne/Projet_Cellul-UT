#include "menu.h"
#include "automatePerso.h"
#include <QtDebug>
#include <QApplication>

// declare the pointers to the class instances which have to be accessible
menu * menu;
Personnalise* perso;
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    menu = new class menu();
    perso= new class Personnalise();

    // show main window
    menu->show();
    return a.exec();
}
