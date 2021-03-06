#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "MyGraphicSceneBB.h"
#include "menu.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindowBB ; }
QT_END_NAMESPACE

class MainWindowBB : public QMainWindow {
Q_OBJECT
public :
    MainWindow(QWidget *parent = nullptr) ;
    ~MainWindow() ;
    // member functions
    void toggleCells(int x, int y, MyGraphicScene * theScene) ;
    int get_CellsPerLine() ;
    int get_ViewResolution() ;
    void set_ViewResolution(int res) ;
    void updateUI() ;
private slots :
    void refreshLoop() ;
    void on_newButton_clicked() ;
    void on_saveButton_clicked() ;
    void on_loadButton_clicked() ;
    void on_playButton_clicked() ;
    void on_pauseButton_clicked() ;
    void on_resetButton_clicked() ;
    void on_backStepButton_clicked() ;
    void on_forwardStepButton_clicked() ;
    void on_loopMs_sliderMoved(int position) ;
    void on_sliderCellsAlive_sliderMoved(int position) ;
    void on_backToStartStep_clicked() ;
    void on_Menu_clicked();
    void on_Loop_clicked();

private :
    // member functions
    void startLoop() ;
    void setStartLoopButtonColor() ;
    // variables
    Ui::MainWindow * ui ;
    MyGraphicScene * scene ; //!< custom scene, where the Game of Life is shown
    QPixmap image ; //!< image to assign to the scene
    int timer ; //!< tracks how many ticks the loop did already run
    int times ; //!< how many times the loop has to run
    int viewResolution ; //!< how many pixel is one side of the view resolution (the view is a square)
    bool loopActive = false ;
    bool loopPause = false ;
} ;

#endif // MAINWINDOW_H
