#ifndef ZOMBIE_H
#define ZOMBIE_H
#include<QGraphicsPixmapItem>
#include <QString>
#include <QLabel>
class Zombie : public QLabel
{
    Q_OBJECT
public:
    Zombie(QWidget* parent, int id);
    char getCharacter();
    void kill();
    bool isDead();
    int getPosition();
    void attack();
public slots:
    void tickReceived();
private:
    int m_id;
    int m_stage=1;
    int m_xPos = 0;
    char m_character;
    int m_currentTick = 0;
    bool m_dying = false;
    bool m_alive = true;
    bool m_dead = false;
    bool m_attack = false;
};

#endif // ZOMBIE_H
