#include "startwindow.h"
#include "ui_startwindow.h"
#include "mainwindow.h"
#include <conio.h>
#include <stdlib.h>
#include <QTextEdit>
#include <QDateTime>
#include <QCoreApplication>


StartWindow::StartWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StartWindow)
{
    ui->setupUi(this);

    button_gamestart = new QPushButton(this);
    button_gameoff = new QPushButton(this);

    button_gamestart->setGeometry(QRect(362,100,300,300));
    button_gamestart->setFlat(true);

    button_gamestart->setIcon(QIcon(QPixmap(":/image/start.png")));
    button_gamestart->setIconSize(QSize(250,250));

    button_gameoff->setGeometry(QRect(300,350,424,300));
    button_gameoff->setFlat(true);

    button_gameoff->setIcon(QIcon(QPixmap(":/image/exit.png")));
    button_gameoff->setIconSize(QSize(400,200));
    connect(button_gamestart,SIGNAL(clicked(bool)),this,SLOT(on_pushButton_gamestart_clicked()));
    connect(button_gameoff,SIGNAL(clicked(bool)),this,SLOT(on_pushButton_gameoff_clicked()));


}

StartWindow::~StartWindow()
{
    delete ui;
}
void StartWindow::paintEvent(QPaintEvent *){
    QPixmap background(":/image/startInterface.png");
    QPainter painter(this);
    painter.drawPixmap(0, 0, background);
}
void StartWindow::on_pushButton_gamestart_clicked(){
    this->hide();
    emit showmainwindow();
}

void StartWindow::on_pushButton_gameoff_clicked(){
    emit quit();
}

void StartWindow::start_show(){
    this->show();
}
