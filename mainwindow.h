#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include "towerposition.h"
#include "tower.h"
#include "barbette.h"
#include "arrowtower.h"
#include "singlecado.h"
#include "tighttowerposi.h"
#include <QMenu>
#include <QPushButton>
#include <QMenuBar>
#include <QAction>

namespace Ui {
class MainWindow;
}
class TowerPosition;
class TightTowerPosi;
class WayPoint;
class Enemy;
class Bullet;
class AudioPlayer;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void getHpDamage(int damage = 1);
    void removedEnemy(Enemy *enemy);
    void removeTower(Tower *tower);
    void removedBullet(Bullet *bullet);
    void addBullet(Bullet *bullet);
    void awardGold(int gold);

    AudioPlayer* audioPlayer() const;
    QList<Enemy *> enemyList() const;

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);

private slots:
    void on_pushbutton_gameoff_clicked();
    void on_pushbutton_home_clicked();
    void construct_tower_1();
    void construct_tower_2();
    void action_levelup();
    void action_remove();
    void updateMap();
    void gameStart();
    void main_show();
    void restart();
    void reset();
    void custom_up();
signals:
    void quit();
    void gobackhome();
    void showmiddlewindow();
    void showlostwindow();
    void showwinwindow();
private:
    void create_construct_Menu();
    void create_lere_Menu();
    void loadTowerPositions();
    void addWayPoints();
    bool loadWave();
    bool canBuyTower() const;
    void drawWave(QPainter *painter);
    void drawHP(QPainter *painter);
    void drawPlayerGold(QPainter *painter);
    void doGameOver();
    void preLoadWavesInfo();

private:
    Ui::MainWindow *		ui;
    int						m_waves;
    int						m_playerHp;
    int						m_playerGold;
    bool					m_gameEnded;
    bool					m_gameWin;
    int                     m_position;
    int                     m_posi;
    int                     m_custom;


    AudioPlayer *			m_audioPlayer;
    QList<QVariant>			m_wavesInfo;
    QList<TowerPosition>	m_towerPositionsList;
    QList<Tower *>			m_towersList;
    QList<WayPoint *>		m_wayPointsList;
    QList<Enemy *>			m_enemyList;
    QList<Bullet *>			m_bulletList;
    QList<TightTowerPosi *> m_TightTowerPosiList;
    TightTowerPosi *        m_tighter;
    QAction *               barbette;
    QAction *               arrowTower;
    QAction *               levelup;
    QAction *               remove;
    QMenu *                 m_menu_construct;
    QMenu *                 m_menu_lere;
    QPushButton *           button_gameoff;
    QPushButton *           button_home;
};

#endif // MAINWINDOW_H
