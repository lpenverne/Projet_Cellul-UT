#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include <QMainWindow>
#include "MyGraphicScene.h"

namespace Ui {
class SecondWindow;
}

class SecondWindow : public QMainWindow {
Q_OBJECT
public :
    // constructor & destructor
    explicit SecondWindow(QWidget *parent = nullptr);
    ~SecondWindow() ;
    // variable
    MyGraphicScene * scene ;
private :
    Ui::SecondWindow * ui ;
} ;

#endif // SecondWindow_H
