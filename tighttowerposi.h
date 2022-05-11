#ifndef TIGHTTOWERPOSI_H
#define TIGHTTOWERPOSI_H
#include <QPoint>
#include "tower.h"
#include "mainwindow.h"

class TightTowerPosi
{
public:
    TightTowerPosi(TightTowerPosi*& tighter);
    TightTowerPosi(QPoint pos, Tower *tower, MainWindow *game);
    const QPoint centerPos() const;
    bool containPoint(const QPoint &pos) const;
    Tower* getTower();
    QPoint getPos();


private:
    Tower* m_tower;
    QPoint m_pos;
    MainWindow *	m_game;

    static const QSize m_fixedSize;
};

#endif // TIGHTTOWERPOSI_H
