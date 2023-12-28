#ifndef ALIEN_H
#define ALIEN_H
#include<QGraphicsPixmapItem>
#include <QString>
#include <QLabel>
class Alien : public QLabel
{
    Q_OBJECT
public:
    Alien(QWidget* parent);
    void kill();
    bool isDead();
signals:
    void alienDead();
public slots:
    void tickReceived();
    void hit();
    void attack();
private:
    int m_stage=1;
    int m_xPos = 0;
    int m_currentTick = 0;
    bool m_dying = false;
    bool m_alive = true;
    bool m_dead = false;
    bool m_hit = false;
    bool m_attack = false;
};

#endif // ALIEN_H
