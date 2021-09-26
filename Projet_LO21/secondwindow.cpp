#include "secondwindow.h"
#include "ui_secondwindow.h"
#include <QDebug>

SecondWindow::SecondWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::SecondWindow) {

    ui->setupUi(this) ;

    // instantiate the scenes and add them to the views
    scene = new MyGraphicScene(this) ;
    ui->graphicsView_1->setScene(scene) ;

    // set the pixel resolution to the scenes (it is used in the paint function)
    scene->myPixelResolution = 320 ;

}

SecondWindow::~SecondWindow() {
    delete ui ;
}


