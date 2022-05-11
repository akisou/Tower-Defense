#ifndef TOWER_H
#define TOWER_H

#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QObject>

class QPainter;
class Enemy;
class MainWindow;
class QTimer;

class Tower : QObject
{
    Q_OBJECT
public:
    Tower(QPoint pos, MainWindow *game, const QPixmap &sprite_1, const QPixmap &sprite_2, const QPixmap &sprite_3,
           const QPixmap &bullet_1, const QPixmap &bullet_2, const QPixmap &bullet_3);
    ~Tower();



	void draw(QPainter *painter) const;
	void checkEnemyInRange();
	void targetKilled();
	void attackEnemy();
	void chooseEnemyForAttack(Enemy *enemy);
	void removeBullet();
	void damageEnemy();
	void lostSightOfEnemy();
    int  getlevel();
    int  getAttackRange();
    int  getCost();
    int  getLevelCost1();
    int  getLevelCost2();
    virtual void levelup(){}


private slots:
    void shootWeapon();

public:

    bool			m_attacking;
    int				m_attackRange;	// 代表塔可以攻击到敌人的距离
    int				m_damage;		// 代表攻击敌人时造成的伤害
    int				m_fireRate;	// 代表再次攻击敌人的时间间隔
    int             m_level;
    int             m_cost;
    int             m_levelCost1;
    int             m_levelCost2;
	qreal			m_rotationSprite;

	Enemy *			m_chooseEnemy;
	MainWindow *	m_game;
	QTimer *		m_fireRateTimer;

    QPoint	        m_pos;
    const QPixmap   m_sprite_1;
    const QPixmap   m_sprite_2;
    const QPixmap   m_sprite_3;
    const QPixmap   m_bullet_1;
    const QPixmap   m_bullet_2;
    const QPixmap   m_bullet_3;


	static const QSize ms_fixedSize;
};

#endif // TOWER_H
