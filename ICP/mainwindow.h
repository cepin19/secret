#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QPixmap>
#include <QRectF>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLabel>
#include "gcard.h"
#include "drag.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



private slots:

    //void paintEvent(QPaintEvent *);

    void on_actionNew_game_triggered();

    void on_actionOpen_a_game_triggered();

    void on_actionNew_instance_triggered();

    void on_actionSave_triggered();

    void on_actionClose_triggered();

    void on_actionAbout_triggered();

    void on_actionShow_moves_triggered();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    QGraphicsScene *scene;
    QPixmap image;
    QPixmap *pixmap;
    QPainter *painter;
    QGraphicsView *graphicsView;
    //DragWidget *drag;
    DragWidget *frame2;
    DragWidget *frame3;

    DragWidget *frame4;

    QLabel *label;
};

#endif // MAINWINDOW_H
