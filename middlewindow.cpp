#include "middlewindow.h"
#include "ui_middlewindow.h"

MiddleWindow::MiddleWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MiddleWindow)
{
    ui->setupUi(this);

    button_nextcustom = new QPushButton(this);
    button_restart = new QPushButton(this);
    button_gameoff = new QPushButton(this);

    button_nextcustom->setGeometry(QRect(362,150,300,100));
    button_nextcustom->setIcon(QIcon(QPixmap(":/image/next.png")));
    button_nextcustom->setIconSize(QSize(300,200));
    button_nextcustom->setFlat(true);

    button_restart->setGeometry(QRect(362,260,300,200));
    button_restart->setIcon(QIcon(QPixmap(":/image/home.png")));
    button_restart->setIconSize(QSize(200,200));
    button_restart->setFlat(true);

    button_gameoff->setGeometry(QRect(362,480,300,200));
    button_gameoff->setIcon(QIcon(QPixmap(":/image/exit.png")));
    button_gameoff->setIconSize(QSize(200,200));
    button_gameoff->setFlat(true);

    connect(button_nextcustom,SIGNAL(clicked(bool)),this,SLOT(on_pushButton_nextcustom_clicked()));
    connect(button_restart,SIGNAL(clicked(bool)),this,SLOT(on_pushButton_restart_clicked()));
    connect(button_gameoff,SIGNAL(clicked(bool)),this,SLOT(on_pushButton_gameoff_clicked()));

}

MiddleWindow::~MiddleWindow()
{
    delete ui;
}
void MiddleWindow::paintEvent(QPaintEvent *){
    QPixmap background(":/image/startInterface.png");
    QPainter painter(this);
    painter.drawPixmap(0, 0, background);
}

void MiddleWindow::on_pushButton_nextcustom_clicked(){
    this->hide();
    emit showsecondcustom();
}

void MiddleWindow::on_pushButton_restart_clicked(){
    this->hide();
    emit gobackhome();
}

void MiddleWindow::on_pushButton_gameoff_clicked(){
    this->hide();
    emit quit();
}

void MiddleWindow::middle_show(){
    this->show();
}
