#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QPushButton>

namespace Ui {
class StartWindow;
}

class StartWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StartWindow(QWidget *parent = 0);
    ~StartWindow();

protected:
    void paintEvent(QPaintEvent *);

private slots:
    void on_pushButton_gamestart_clicked();
    void on_pushButton_gameoff_clicked();
    void start_show();
signals:
    void showmainwindow();
    void quit();
private:
    Ui::StartWindow *ui;
    QPushButton *button_gamestart;
    QPushButton *button_gameoff;
};


#endif // STARTWINDOW_H
