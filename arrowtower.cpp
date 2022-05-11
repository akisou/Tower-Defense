#include "arrowtower.h"
#include "tower.h"
#include "enemy.h"
#include "bullet.h"
#include "mainwindow.h"
#include "utility.h"
#include <QPainter>
#include <QColor>
#include <QTimer>
#include <QVector2D>
#include <QtMath>

Arrowtower::Arrowtower(QPoint pos, MainWindow *game,
        const QPixmap &sprite_1 /*= QPixmap(":/image/tower_arrow1.png")*/,
        const QPixmap &sprite_2 /*= QPixmap(":/image/tower_arrow2.png")*/,
        const QPixmap &sprite_3 /*= QPixmap(":/image/tower_arrow3.png")*/,
        const QPixmap &bullet_1 /*= QPixmap(":/image/bullet.png")*/,
        const QPixmap &bullet_2 /*= QPixmap(":/image/bullet.png")*/,
        const QPixmap &bullet_3 /*= QPixmap(":/image/bullet.png")*/)
    : Tower(pos,game,sprite_1,sprite_2,sprite_3,bullet_1,bullet_2,bullet_3)

{
     m_attackRange = 100;
     m_damage = 20;
     m_cost = 300;
     m_levelCost1 = 150;
     m_levelCost2 = 200;
}


void Arrowtower::levelup(){
    m_level++;
    if(m_level == 2){
        m_attackRange = 120 ;
        m_damage = 30;
        m_fireRate = 800;
    }else if(m_level == 3){
        m_attackRange = 140;
        m_damage = 40;
        m_fireRate = 600;
    }
}


