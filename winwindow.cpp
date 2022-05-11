#include "winwindow.h"
#include "ui_winwindow.h"

WinWindow::WinWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WinWindow)
{
    ui->setupUi(this);

    button_home->setGeometry(QRect(362,180,300,300));
    button_home->setIcon(QIcon(QPixmap(":/image/home.png")));
    button_home->setIconSize(QSize(300,300));
    button_home->setFlat(true);

    button_gameoff->setGeometry(QRect(362,480,300,200));
    button_gameoff->setIcon(QIcon(QPixmap(":/image/exit.png")));
    button_gameoff->setIconSize(QSize(200,200));
    button_gameoff->setFlat(true);

    connect(button_home,SIGNAL(clicked(bool)),this,SLOT(on_pushButton_home_clicked()));
    connect(button_gameoff,SIGNAL(clicked(bool)),this,SLOT(on_pushButton_gameoff_clicked()));

}

WinWindow::~WinWindow()
{
    delete ui;
}
void WinWindow::paintEvent(QPaintEvent *){
    QPixmap background(":/image/startInterface.png");
    QPainter painter(this);
    painter.drawPixmap(0, 0, background);
}
void WinWindow::on_pushButton_home_clicked(){
    this->hide();
    emit gobackhome();
}

void WinWindow::on_pushButton_gameoff_clicked(){
    emit quit();
}

void WinWindow::Win_show(){
    this->show();
}
