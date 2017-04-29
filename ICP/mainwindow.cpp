#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "game.h"
#include "QGraphicsObject"

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // QGraphicsScene *scene=new QGraphicsScene(this);
    //graphicsView=new QGraphicsView(scene);
    //graphicsView->show();
    // setFixedSize(500, 500);
    //DragWidget drag=new DragWidget;
    //drag = new  DragWidget (this);


    //create the rectangle
    //QGraphicsRectItem * rect = new QGraphicsRectItem();
    //rect->setRect(0,0,50,50);
    //Card *karta = new Card();

    // Card * karta = new Card();


    //add the item into the scene
    //    scene->addItem(rect);

    //use the view from the mainwindow
    //  graphicsView = new QGraphicsView(scene);
    // this->setCentralWidget(graphicsView); //Assuming 'this' is the QMainWindow widget.
    // graphicsView->show();

    //        QPainter painter(this);
    //        int position = 10;
    //        QRect car(position,120, 60, 120 );
    //        painter.drawPixmap(car, QPixmap("C:/Dropbox/ICP/ICP/Playing Cards/PNG-cards-1.3/2_of_clubs.png").scaled(car.width(), car.height()));



    // TODO tohle funguje !!!!!!!!!!!!
    //    label = new QLabel(this);
    //    pixmap =new QPixmap(500, 500);
    //    pixmap->fill(Qt::transparent);
    //    painter =new QPainter(pixmap);

    // TODO tohle funguje !!!!!!!!!!!!
    //    image.load("C:/Dropbox/ICP/ICP/Playing Cards/PNG-cards-1.3/2_of_clubs.png");
    //    scene = new QGraphicsScene(this);
    //    scene->addPixmap(image);
    //    scene->setSceneRect(image.rect());
    //    ui->mainImage->setScene(scene);





}


/*void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    int position = 10;
    QRect car(position,120, 60, 120 );
    painter.drawPixmap(car, QPixmap("C:/Dropbox/ICP/ICP/Playing Cards/PNG-cards-1.3/2_of_clubs.png").scaled(car.width(), car.height()));
}
*/
MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_game_triggered()
{

    QWidget::update();
    //    QPixmap pixmap1("C:/Dropbox/ICP/ICP/Playing Cards/PNG-cards-1.3/2_of_clubs.png");
    //    QPixmap pixmap2("C:/Dropbox/ICP/ICP/Playing Cards/PNG-cards-1.3/3_of_clubs.png");
    //    painter->drawPixmap(50, 50, 50, 100, pixmap1);
    //    painter->drawPixmap(100, 100, 50, 100, pixmap2);
    //    painter->end();

    //    label->setPixmap(*pixmap);
    //    label->resize(QSize(500,500));

}

void MainWindow::on_actionOpen_a_game_triggered()
{

}

void MainWindow::on_actionNew_instance_triggered()
{
    this->setFixedSize(1500,800);
    ui->frame->setGeometry(QRect(0, 0, this->width()*0.5, this->height()*0.5));

    frame2 = new DragWidget(ui->centralWidget);
    frame2->setObjectName(QStringLiteral("frame2"));
    frame2->setGeometry(QRect(this->width()*0.5, 0, this->width()*0.5, this->height()*0.5));
    frame2->setStyleSheet("background-color : rgb(50, 150, 50)");
    frame2->setFrameShape(QFrame::StyledPanel);
    frame2->setFrameShadow(QFrame::Raised);
    //ui->MainWindow->addWidget(frame2);
    frame2->show();
    frame3 = new DragWidget(ui->centralWidget);
    frame3->setObjectName(QStringLiteral("frame3"));
    frame3->setGeometry(QRect(0, this->height()*0.5, this->width()*0.5, this->height()*0.5));
    frame3->setFrameShape(QFrame::StyledPanel);
    frame3->setFrameShadow(QFrame::Raised);
    frame3->setStyleSheet("background-color : rgb(50, 150, 50)");

    frame3->show();
    frame4 = new DragWidget(ui->centralWidget);
    frame4->setObjectName(QStringLiteral("frame4"));
    frame4->setGeometry(QRect(this->width()*0.5, this->height()*0.5, this->width()*0.5, this->height()*0.5));
    frame4->setFrameShape(QFrame::StyledPanel);
    frame4->setFrameShadow(QFrame::Raised);
    frame4->setStyleSheet("background-color : rgb(50, 150, 50)");

    frame4->show();

}

void MainWindow::on_actionSave_triggered()
{

}

void MainWindow::on_actionClose_triggered()
{

}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, tr("About Application"),
                       tr("Popis <b>SOLITARIE</b>."));
}

void MainWindow::on_actionShow_moves_triggered()
{
    ui->frame->g->print_possible_moves();
}

void MainWindow::on_pushButton_clicked()
{
    ui->frame->g->print_possible_moves();
}
