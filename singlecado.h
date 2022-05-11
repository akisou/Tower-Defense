#ifndef SINGLECADO_H
#define SINGLECADO_H

#include <QObject>
#include <QPoint>
#include <QSize>
#include <QPixmap>
#include "waypoint.h"
#include <QPainter>
#include "mainwindow.h"
#include "tower.h"

class Enemy;

class singlecado : public Enemy
{
public:
    singlecado(WayPoint *startWayPoint, MainWindow *game, const QPixmap &sprite = QPixmap(":/image/singlecado.png"));

};

#endif // SINGLECADO_H
