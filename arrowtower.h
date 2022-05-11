#ifndef ARROWTOWER_H
#define ARROWTOWER_H

#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QObject>
#include <QPainter>
#include "enemy.h"
#include "mainwindow.h"
#include <QTimer>

class Tower;

class Arrowtower : public Tower{
public:
    Arrowtower(QPoint pos, MainWindow *game,
            const QPixmap &sprite_1 = QPixmap(":/image/tower_arrow1.png"),
            const QPixmap &sprite_2 = QPixmap(":/image/tower_arrow2.png"),
            const QPixmap &sprite_3 = QPixmap(":/image/tower_arrow3.png"),
            const QPixmap &bullet_1 = QPixmap(":/image/bullet.png"),
            const QPixmap &bullet_2 = QPixmap(":/image/bullet.png"),
            const QPixmap &bullet_3 = QPixmap(":/image/magic1.png"));
    void levelup();
};

#endif // ARROWTOWER_H
