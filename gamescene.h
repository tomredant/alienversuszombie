#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QObject>
#include<zombie.h>
#include <QTimer>
#include <QWidget>
class Alien;
class GameScene : public QWidget
{
    Q_OBJECT
public:
    explicit GameScene(QWidget *parent = nullptr);
    ~GameScene();
signals:
    void tick();
    void updateScore();
    void alienHit();
    void alienAttack();
    void alienDead();
public slots:
    void tickReceived();
    void charNotified(char character);
    void alienDeadReceived();
private:
    QVector<Zombie*> m_zombies;
    QTimer * p_timer;
    QTimer * p_timerFast;
    qint64 m_startTime;
    Alien* m_alien;
    int m_numAlienHits = 0;

};

#endif // GAMESCENE_H
