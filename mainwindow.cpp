#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "waypoint.h"
#include "enemy.h"
#include "bullet.h"
#include "tighttowerposi.h"
#include "audioplayer.h"
#include "plistreader.h"
#include <QPainter>
#include <QMouseEvent>
#include <QtGlobal>
#include <QMessageBox>
#include <QTimer>
#include <QXmlStreamReader>
#include <QtDebug>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QTextEdit>
#include <QDateTime>
#include <QCoreApplication>

static const int TowerCost = 300;

MainWindow::MainWindow(QWidget *parent)
   : QMainWindow(parent)
   , ui(new Ui::MainWindow)
   , m_waves(0)
   , m_playerHp(5)
   , m_playerGold(600)
   , m_gameEnded(false)
   , m_gameWin(false)
   , m_tighter(NULL)
   , m_posi(NULL)
   , m_position(0)
   , m_custom(1)
{
   ui->setupUi(this);
   preLoadWavesInfo();
   loadTowerPositions();
   addWayPoints();

   button_gameoff = new QPushButton(this);
   button_home = new QPushButton(this);
   button_home->setGeometry(QRect(50,50,100,25));
   button_home->setText("Home");
   button_gameoff->setGeometry(QRect(150,50,200,25));
   button_gameoff->setText("Game off");
   connect(button_home,SIGNAL(clicked(bool)),this,SLOT(on_pushbutton_home_clicked()));
   connect(button_gameoff,SIGNAL(clicked(bool)),this,SLOT(on_pushbutton_gameoff_clicked()));


  /* m_audioPlayer = new AudioPlayer(this);
   m_audioPlayer->startBGM();

   QMediaPlayer * player = new QMediaPlayer;
   player->setMedia(QUrl(":/music/bgm.mp3"));
   player->setVolume(100);
   player->play();*/

   QTimer *timer = new QTimer(this);
   connect(timer, SIGNAL(timeout()), this, SLOT(updateMap()));

   timer->start(30);

   // 设置300ms后游戏启动
   //QTimer::singleShot(300, this, SLOT(gameStart()));
}

MainWindow::~MainWindow()
{
   delete ui;
}

void MainWindow::loadTowerPositions()
{
   QFile file(":/config/TowersPosition.plist");
   if (!file.open(QFile::ReadOnly | QFile::Text))
   {
       QMessageBox::warning(this, "TowerDefense", "Cannot Open TowersPosition.plist");
       return;
   }
   PListReader reader;
   if(m_custom == 1)reader.read(&file);
   else if(m_custom == 2)reader.read(&file);

   QList<QVariant> array = reader.data();
   foreach (QVariant dict, array)
   {
       QMap<QString, QVariant> point = dict.toMap();
       int x = point.value("x").toInt();
       int y = point.value("y").toInt();
       //TowerPosition *Position = new TowerPosition(QPoint(x,y), NULL, QPixmap(":/image/open_spot.png"));
       m_towerPositionsList.push_back(QPoint(x,y));
   }
   file.close();
}

void MainWindow::paintEvent(QPaintEvent *)
{
   if(m_custom ==1){
       QPixmap cachePix(":/image/chizu.1.png");
       QPainter cachePainter(&cachePix);

       foreach (const TowerPosition &towerPos, m_towerPositionsList)
           towerPos.draw(&cachePainter);

       foreach (const Tower *tower, m_towersList)
           tower->draw(&cachePainter);

       foreach (const WayPoint *wayPoint, m_wayPointsList)
           wayPoint->draw(&cachePainter);

       foreach (const Enemy *enemy, m_enemyList)
           enemy->draw(&cachePainter);

       foreach (const Bullet *bullet, m_bulletList)
           bullet->draw(&cachePainter);

       drawWave(&cachePainter);
       drawHP(&cachePainter);
       drawPlayerGold(&cachePainter);

       QPainter painter(this);
       painter.drawPixmap(0, 0, cachePix);
   }else if(m_custom == 2){
       QPixmap cachePix(":/image/chizu.1.png");
       QPainter cachePainter(&cachePix);

       foreach (const TowerPosition &towerPos, m_towerPositionsList)
           towerPos.draw(&cachePainter);

       foreach (const Tower *tower, m_towersList)
           tower->draw(&cachePainter);

       foreach (const WayPoint *wayPoint, m_wayPointsList)
           wayPoint->draw(&cachePainter);

       foreach (const Enemy *enemy, m_enemyList)
           enemy->draw(&cachePainter);

       foreach (const Bullet *bullet, m_bulletList)
           bullet->draw(&cachePainter);

       drawWave(&cachePainter);
       drawHP(&cachePainter);
       drawPlayerGold(&cachePainter);

       QPainter painter(this);
       painter.drawPixmap(0, 0, cachePix);
   }


}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
   QPoint pressPos = event->pos();
   auto it = m_towerPositionsList.begin();
   while (it != m_towerPositionsList.end())
   {
       if (canBuyTower() && it->containPoint(pressPos) && !it->hasTower())
       {
           for(int i=0;i<m_towerPositionsList.size();i++){
               if(m_towerPositionsList[i].getPos() == it->getPos()){
                   m_posi = i;
               }
           }
           create_construct_Menu();
           m_menu_construct->popup(event->globalPos());
           break;
       }
       else if(it->hasTower() && it->containPoint(pressPos) ){
           for(int i=0;i<m_towerPositionsList.size();i++){
               if(m_towerPositionsList[i].getPos() == it->getPos()){
                   m_position = i;
               }
           }

           auto subit = m_TightTowerPosiList.begin();
           while (subit != m_TightTowerPosiList.end()){
               TightTowerPosi *it_1 = *subit;
               if(it_1->containPoint(pressPos)){
                   m_tighter = it_1;
                   create_lere_Menu();
                   m_menu_lere->popup(event->globalPos());
                   break;
               }
               ++subit;
           }
       }
       ++it;
   }
}

bool MainWindow::canBuyTower() const
{
   if (m_playerGold >= TowerCost)
       return true;
   return false;
}

void MainWindow::drawWave(QPainter *painter)
{
   painter->setPen(QPen(Qt::red));
   painter->drawText(QRect(400, 5, 100, 25), QString("WAVE : %1").arg(m_waves + 1));
}

void MainWindow::drawHP(QPainter *painter)
{
   painter->setPen(QPen(Qt::red));
   painter->drawText(QRect(30, 5, 100, 25), QString("HP : %1").arg(m_playerHp));
}

void MainWindow::drawPlayerGold(QPainter *painter)
{
   painter->setPen(QPen(Qt::red));
   painter->drawText(QRect(200, 5, 200, 25), QString("GOLD : %1").arg(m_playerGold));
   const QPixmap gold = QPixmap(":/image/icon_gold.png");
   painter->drawPixmap(175,3,gold);
}

void MainWindow::doGameOver()
{

   if (!m_gameEnded)
   {
       /*QMediaPlayer * player2 = new QMediaPlayer;
       player2->setMedia(QUrl(":/music/lose.mp3"));
       player2->setVolume(100);
       player2->play();*/


       m_gameEnded = true;
       this->hide();
       emit showlostwindow();
       // 此处应该切换场景到结束场景
       // 暂时以打印替代,见paintEvent处理
   }
}

void MainWindow::awardGold(int gold)
{
   m_playerGold += gold;
   update();
}

AudioPlayer *MainWindow::audioPlayer() const
{
   return m_audioPlayer;
}

void MainWindow::addWayPoints()
{
   /*WayPoint *wayPoint[10] = {new WayPoint(QPoint(0,0)),new WayPoint(QPoint(425,90)),new WayPoint(QPoint(425,150)),new WayPoint(QPoint(381,150))
                             ,new WayPoint(QPoint(381,245)),new WayPoint(QPoint(245,245)),new WayPoint(QPoint(245,81))
                             ,new WayPoint(QPoint(108,81)),new WayPoint(QPoint(108,180)),new WayPoint(QPoint(30,180))};
   m_wayPointsList.push_back(wayPoint[1]);
   for(int i=2;i<=10;i++){
       m_wayPointsList.push_back(wayPoint[i]);
       wayPoint[i+1]->setNextWayPoint(wayPoint[i+1]);
   }
}
   */
   if(m_custom == 1 || m_custom == 2 ){
   WayPoint *wayPoint1 = new WayPoint(QPoint(1030, 416));
   m_wayPointsList.push_back(wayPoint1);

   WayPoint *wayPoint2 = new WayPoint(QPoint(736, 416));
   m_wayPointsList.push_back(wayPoint2);
   wayPoint2->setNextWayPoint(wayPoint1);

   WayPoint *wayPoint3 = new WayPoint(QPoint(736, 224));
   m_wayPointsList.push_back(wayPoint3);
   wayPoint3->setNextWayPoint(wayPoint2);

   WayPoint *wayPoint4 = new WayPoint(QPoint(608,224));
   m_wayPointsList.push_back(wayPoint4);
   wayPoint4->setNextWayPoint(wayPoint3);

   WayPoint *wayPoint5 = new WayPoint(QPoint(608, 672));
   m_wayPointsList.push_back(wayPoint5);
   wayPoint5->setNextWayPoint(wayPoint4);

   WayPoint *wayPoint6 = new WayPoint(QPoint(224,672));
   m_wayPointsList.push_back(wayPoint6);
   wayPoint6->setNextWayPoint(wayPoint5);

   WayPoint *wayPoint7 = new WayPoint(QPoint(224,480));
   m_wayPointsList.push_back((wayPoint7));
   wayPoint7->setNextWayPoint(wayPoint6);

   WayPoint *wayPoint8 = new WayPoint(QPoint(416,480));
   m_wayPointsList.push_back((wayPoint8));
   wayPoint8->setNextWayPoint(wayPoint7);

   WayPoint *wayPoint9 = new WayPoint(QPoint(416,224));
   m_wayPointsList.push_back((wayPoint9));
   wayPoint9->setNextWayPoint(wayPoint8);

   WayPoint *wayPoint10 = new WayPoint(QPoint(96,224));
   m_wayPointsList.push_back((wayPoint10));
   wayPoint10->setNextWayPoint(wayPoint9);

   WayPoint *wayPoint11 = new WayPoint(QPoint(96,352));
   m_wayPointsList.push_back((wayPoint11));
   wayPoint11->setNextWayPoint(wayPoint10);

   WayPoint *wayPoint12 = new WayPoint(QPoint(224,352));
   m_wayPointsList.push_back((wayPoint12));
   wayPoint12->setNextWayPoint(wayPoint11);

   WayPoint *wayPoint13 = new WayPoint(QPoint(224,96));
   m_wayPointsList.push_back((wayPoint13));
   wayPoint13->setNextWayPoint(wayPoint12);

   WayPoint *wayPoint14 = new WayPoint(QPoint(32,96));
   m_wayPointsList.push_back((wayPoint14));
   wayPoint14->setNextWayPoint(wayPoint13);
   }
}



void MainWindow::getHpDamage(int damage/* = 1*/)
{
    /*QMediaPlayer * player = new QMediaPlayer;
    player->setMedia(QUrl(":/music/life_lose.wav"));
    player->setVolume(100);
    player->play();*/

  // m_audioPlayer->playSound(LifeLoseSound);
   m_playerHp -= damage;
   if (m_playerHp <= 0)
       doGameOver();
}

void MainWindow::removedEnemy(Enemy *enemy)
{
   Q_ASSERT(enemy);

   m_enemyList.removeOne(enemy);
   delete enemy;

   if (m_enemyList.empty())
   {
       ++m_waves;
       if (!loadWave())
       {
           m_gameWin = true;

           /*QMediaPlayer * player = new QMediaPlayer;
           player->setMedia(QUrl(":/music/win.mp3"));
           player->setVolume(100);
           player->play();*/


           this->hide();
           if(m_custom == 1)emit showmiddlewindow();
           else if(m_custom == 2)emit showwinwindow();
           // 游戏胜利转到游戏胜利场景
           // 这里暂时以打印处理
       }
   }
}

void MainWindow::removeTower(Tower *tower){
   Q_ASSERT(tower);

   m_towerPositionsList[m_position].setHasnoTower();
   m_towersList.removeOne(tower);
   delete tower;
}

void MainWindow::removedBullet(Bullet *bullet)
{
   Q_ASSERT(bullet);

   m_bulletList.removeOne(bullet);
   delete bullet;
}

void MainWindow::addBullet(Bullet *bullet)
{
   Q_ASSERT(bullet);

   m_bulletList.push_back(bullet);
}

void MainWindow::updateMap()
{
   foreach (Enemy *enemy, m_enemyList)
       enemy->move();
   foreach (Tower *tower, m_towersList)
       tower->checkEnemyInRange();
   update();
}

void MainWindow::preLoadWavesInfo()
{
   QFile file(":/config/Waves.plist");
   if (!file.open(QFile::ReadOnly | QFile::Text))
   {
       QMessageBox::warning(this, "TowerDefense", "Cannot Open TowersPosition.plist");
       return;
   }
   PListReader reader;
   if(m_custom == 1)reader.read(&file);
   else if(m_custom ==2)reader.read(&file);
   m_wavesInfo = reader.data();
   file.close();
}

bool MainWindow::loadWave()
{
   if (m_waves >= m_wavesInfo.size())
       return false;

   WayPoint *startWayPoint = m_wayPointsList.back();
   QList<QVariant> curWavesInfo = m_wavesInfo[m_waves].toList();

   for (int i = 0; i < curWavesInfo.size(); ++i)
   {
       QMap<QString, QVariant> dict = curWavesInfo[i].toMap();
       int spawnTime = dict.value("spawnTime").toInt();

       if(dict.value("type") == "singlecado"){
           Enemy *enemy = new singlecado(startWayPoint, this);
           m_enemyList.push_back(enemy);
           QTimer::singleShot(spawnTime, enemy, SLOT(doActivate()));
       }else if(dict.value("type") == "enemy"){
           Enemy *enemy = new Enemy(startWayPoint, this);
           m_enemyList.push_back(enemy);
           QTimer::singleShot(spawnTime, enemy, SLOT(doActivate()));
       }

   }

   return true;
}

QList<Enemy *> MainWindow::enemyList() const
{
   return m_enemyList;
}

void MainWindow::gameStart()
{
   loadWave();
}

void MainWindow::create_construct_Menu(){
   m_menu_construct = new QMenu(this);
   QString str;

   barbette = new QAction(m_menu_construct);
   Barbette *bar = new Barbette(QPoint(0,0),this);
   str = QString("%1").arg(bar->getCost());
   barbette->setText("建造炮塔 $ "+ str);
   barbette->setIcon(QPixmap(":/image/icon_turret1.png"));
   delete bar;

   arrowTower = new QAction(m_menu_construct);
   Arrowtower *arrow = new Arrowtower(QPoint(0,0),this);
   str = QString("%1").arg(arrow->getCost());
   arrowTower->setText("建造箭塔 $ " + str);
   arrowTower->setIcon(QPixmap(":/image/icon_arrow1.png"));
   delete arrow;

   m_menu_construct->addAction(barbette);
   m_menu_construct->addAction(arrowTower);

   connect(arrowTower,SIGNAL(triggered()),this,SLOT(construct_tower_1()));
   connect(barbette,SIGNAL(triggered()),this,SLOT(construct_tower_2()));

}

void MainWindow::create_lere_Menu(){
    m_menu_lere = new QMenu(this);

    levelup = new QAction(m_menu_lere);
    QString str;
    if(m_tighter->getTower()->getlevel() == 1)str = QString("%1").arg(m_tighter->getTower()->getLevelCost1());
    else if(m_tighter->getTower()->getlevel() == 2)str = QString("%1").arg(m_tighter->getTower()->getLevelCost2());

    levelup->setText("level up $ "+str);
    levelup->setIcon(QPixmap(":/image/level_up.png"));

    remove = new QAction(m_menu_lere);
    if(m_tighter->getTower()->getlevel() == 1)str = QString("%1").arg(m_tighter->getTower()->getCost() - 50);
    else if(m_tighter->getTower()->getlevel() == 2)str = QString("%1").arg(m_tighter->getTower()->getLevelCost1() - 50);
    else if(m_tighter->getTower()->getlevel() == 3)str = QString("%1").arg(m_tighter->getTower()->getLevelCost2() - 50);
    remove->setText("remove it $ " + str);
    remove->setIcon(QPixmap(":/image/remove.png"));

    m_menu_lere->addAction(levelup);
    m_menu_lere->addAction(remove);

    connect(levelup,SIGNAL(triggered()),this,SLOT(action_levelup()));
    connect(remove,SIGNAL(triggered()),this,SLOT(action_remove()));
}

void MainWindow::construct_tower_1(){
   Tower *tower = new Arrowtower(m_towerPositionsList[m_posi].centerPos(), this);
   if (m_playerGold >= tower->getCost())
   {
       //m_audioPlayer->playSound(TowerPlaceSound);
       /*QMediaPlayer * player = new QMediaPlayer;
       player->setMedia(QUrl(":/music/tower_place.wav"));
       player->setVolume(100);
       player->play();*/


       m_playerGold -= tower->getCost();
       m_towerPositionsList[m_posi].setHasTower();

       TightTowerPosi *tight = new TightTowerPosi(m_towerPositionsList[m_posi].getPos(), tower, this);
       m_towersList.push_back(tower);
       m_TightTowerPosiList.push_back(tight);
       update();
       return ;
   }
   m_menu_construct->exec();
}
void MainWindow::construct_tower_2(){
   Tower *tower = new Barbette(m_towerPositionsList[m_posi].centerPos(), this);
   if (m_playerGold >= tower->getCost())
   {
       /*QMediaPlayer * player = new QMediaPlayer;
       player->setMedia(QUrl(":/music/tower_place.wav"));
       player->setVolume(100);
       player->play();*/


       m_playerGold -= tower->getCost();
       m_towerPositionsList[m_posi].setHasTower();

       TightTowerPosi *tight = new TightTowerPosi(m_towerPositionsList[m_posi].getPos(), tower, this);
       m_towersList.push_back(tower);
       m_TightTowerPosiList.push_back(tight);
       update();
       return ;
   }
   m_menu_construct->exec();
}
void MainWindow::action_levelup(){
   if(m_tighter->getTower()->getlevel() < 3){
       if(m_tighter->getTower()->getlevel() == 1 && m_playerGold >= m_tighter->getTower()->getLevelCost1()){
           m_playerGold -= m_tighter->getTower()->getLevelCost1();
           m_tighter->getTower()->levelup();

           /*QMediaPlayer * player = new QMediaPlayer;
           player->setMedia(QUrl(":/music/tower_place.wav"));
           player->setVolume(100);
           player->play();*/
       }
       else if(m_tighter->getTower()->getlevel() == 2 && m_playerGold >= m_tighter->getTower()->getLevelCost2()){
           m_playerGold -= m_tighter->getTower()->getLevelCost2();
           m_tighter->getTower()->levelup();

           /*QMediaPlayer * player = new QMediaPlayer;
           player->setMedia(QUrl(":/music/tower_place.wav"));
           player->setVolume(100);
           player->play();*/
       }
       m_menu_lere->exec();
   }
}
void MainWindow::action_remove(){
   if(m_TightTowerPosiList.indexOf(m_tighter) < 0){return;}
   else if(m_tighter->getTower()->getlevel() == 1){
       removeTower(m_tighter->getTower());
       m_playerGold += m_tighter->getTower()->getCost() -50;
       m_TightTowerPosiList.removeOne(m_tighter);
       m_menu_lere->exec();
   }
   else if(m_tighter->getTower()->getlevel() == 2){
       removeTower(m_tighter->getTower());
       m_playerGold += m_tighter->getTower()->getLevelCost1() -50;
       m_TightTowerPosiList.removeOne(m_tighter);
       m_menu_lere->exec();
   }
   else if(m_tighter->getTower()->getlevel() == 3){
       removeTower(m_tighter->getTower());
       m_playerGold += m_tighter->getTower()->getLevelCost2() -50;
       m_TightTowerPosiList.removeOne(m_tighter);
       m_menu_lere->exec();
   }
}

void MainWindow::on_pushbutton_home_clicked(){
    this->hide();
    emit gobackhome();
}

void MainWindow::on_pushbutton_gameoff_clicked(){
    this->hide();
    emit quit();
}

void MainWindow::main_show(){
    m_custom = 1;
    reset();
    this->show();
    gameStart();
}

void MainWindow::restart(){
    reset();
    this->show();
    gameStart();
}

void MainWindow::reset(){
    m_enemyList.clear();
    m_towerPositionsList.clear();
    m_wavesInfo.clear();
    m_wayPointsList.clear();
    m_TightTowerPosiList.clear();
    m_towersList.clear();
    m_waves = 0;
    m_playerGold = 600;
    m_playerHp = 5;
    m_gameEnded = false;
    m_gameWin = false;
    preLoadWavesInfo();
    loadTowerPositions();
    addWayPoints();
}

void MainWindow::custom_up(){
    m_custom = 2;
    reset();
    this->show();
    gameStart();
}




