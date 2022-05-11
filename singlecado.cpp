#include "singlecado.h"
#include "enemy.h"
#include "waypoint.h"
#include "tower.h"
#include "utility.h"
#include "mainwindow.h"
#include "audioplayer.h"
#include <QPainter>
#include <QColor>
#include <QDebug>
#include <QMatrix>
#include <QVector2D>
#include <QtMath>

singlecado::singlecado(WayPoint *startWayPoint, MainWindow *game, const QPixmap &sprite /*= QPixmap(":/image/singlecado.png")*/)
    : Enemy(startWayPoint, game,sprite)
{
    m_maxHp = 50;
    m_currentHp = 50;
    m_walkingSpeed = 3.0;
}
