#include "lostwindow.h"
#include "ui_lostwindow.h"

LostWindow::LostWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LostWindow)
{
    ui->setupUi(this);

    button_home = new QPushButton(this);
    button_gameoff = new QPushButton(this);
    button_restart = new QPushButton(this);


    button_home->setGeometry(QRect(362,120,300,200));
    button_home->setIcon(QIcon(QPixmap(":/image/home.png")));
    button_home->setIconSize(QSize(300,200));
    button_home->setFlat(true);

    button_gameoff->setGeometry(QRect(362,490,300,250));
    button_gameoff->setIcon(QIcon(QPixmap(":/image/exit.png")));
    button_gameoff->setIconSize(QSize(300,200));
    button_gameoff->setFlat(true);

    button_restart->setGeometry(QRect(362,330,300,200));
    button_restart->setIcon(QIcon(QPixmap(":/image/again.png")));
    button_restart->setIconSize(QSize(200,100));
    button_restart->setFlat(true);

    connect(button_home,SIGNAL(clicked(bool)),this,SLOT(on_pushButton_home_clicked()));
    connect(button_gameoff,SIGNAL(clicked(bool)),this,SLOT(on_pushButton_gameoff_clicked()));
    connect(button_restart,SIGNAL(clicked(bool)),this,SLOT(on_pushButton_restart_clicked()));
}

LostWindow::~LostWindow()
{
    delete ui;
}

void LostWindow::paintEvent(QPaintEvent *){
    QPixmap background(":/image/startInterface.png");
    QPainter painter(this);
    painter.drawPixmap(0, 0, background);
}
void LostWindow::on_pushButton_home_clicked(){
    this->hide();
    emit gobackhome();
}

void LostWindow::on_pushButton_gameoff_clicked(){
    emit quit();
}

void LostWindow::on_pushButton_restart_clicked(){
    this->hide();
    emit showmainwindow();
}

void LostWindow::lost_show(){
    this->show();
}
