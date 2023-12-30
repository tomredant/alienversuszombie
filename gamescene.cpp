#include "gamescene.h"
#include<stdlib.h>
#include <QDateTime>
#include "math.h"
#include "gameproperties.h"
#include "alien.h"
GameScene::GameScene(QWidget *parent) : QWidget(parent)
{

    QLabel* backGround = new QLabel(this);
    QPixmap map(":/pic/2_game_background.png");
    backGround->setPixmap(map);
    m_alien = new Alien(this);
    connect(this, SIGNAL(tick()), m_alien, SLOT(tickReceived()));
    connect(m_alien, SIGNAL(alienDead()), this, SLOT(alienDeadReceived()));
    m_numAlienHits = 0;
}


GameScene::~GameScene() {
    for(int i=0;i<m_zombies.size();i++)
        delete m_zombies[i];
}


void GameScene::charNotified(char character) {
    if(m_alien->getAmountOfBullets() > 0) {
        m_alien->attack();
        emit alienAttack();
        for(int i=0;i<m_zombies.size();i++) {
            if((character == m_zombies[i]->getCharacter()) && m_zombies[i]->isAlive()) {
                m_zombies[i]->kill();
                for(int i=0;i<BULLET_REGAIN_AFTER_HIT;i++)
                    m_alien->increaseAmountOfBullets();
                emit updateScore();
                return; // only kill a single zombie
            }
        }
    }
}


void GameScene::alienDeadReceived() {
    emit alienDead();
}
void GameScene::tickReceived() {

    if((rand() % ZOMBIE_SELDOMNESS) == 0) {
        qint64 currentTime = QDateTime::currentMSecsSinceEpoch();
        if((currentTime - m_lastZombieCreationTime) > MINIMUM_ZOMBIE_INTERVAL_MS) {
            m_lastZombieCreationTime=currentTime;
            m_zombies.append(new Zombie(this, (rand() % 3) + 1));
            m_zombies.last()->show();
            connect(this, SIGNAL(tick()), m_zombies.last(), SLOT(tickReceived()));
        }
    }



    for(int i=0;i<m_zombies.size();i++) {
        if(m_zombies[i]->isDead()) {
            delete m_zombies[i];
            m_zombies.removeAt(i);
        }
        //TODO: also delete zombies when being too long on the screen or going off screen...
    }


    for(int i=0;i<m_zombies.size();i++) {
        if(m_zombies[i]->getPosition() >= (ALIEN_POSITION+150)) {
            m_zombies[i]->attack();
            m_zombies.removeAt(i);
            m_numAlienHits++;
            if(m_numAlienHits == MAX_NUM_ALIEN_HITS)
                m_alien->kill();
            else {
                m_alien->hit();
            }
            m_alien->resetAmountOfBullets();
            emit alienHit();
        }
    }
    emit tick();


}
