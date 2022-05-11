#ifndef BARBETTE_H
#define BARBETTE_H


#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QObject>
#include <QPainter>
#include "enemy.h"
#include "mainwindow.h"
#include <QTimer>

class Tower;

class Barbette : public Tower{
public:
    Barbette(QPoint pos, MainWindow *game,
            const QPixmap &sprite_1 = QPixmap(":/image/Tower-turret1.png"),
            const QPixmap &sprite_2 = QPixmap(":/image/Tower-turret2.png"),
            const QPixmap &sprite_3 = QPixmap(":/image/Tower-turret3.png"),
            const QPixmap &bullet_1 = QPixmap(":/image/bullet.png"),
            const QPixmap &bullet_2 = QPixmap(":/image/bullet.png"),
            const QPixmap &bullet_3 = QPixmap(":/image/magic1.png"));
    void levelup();
};

#endif // BARBETTE_H
