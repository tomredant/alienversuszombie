#include "alien.h"
#include<QPixmap>
#include<QDebug>
#include<QCursor>
#include <QPainter>
Alien::Alien(QWidget* parent): QLabel(parent)
{
    hide();
    m_xPos = ALIEN_POSITION;
    m_currentTick = 0;
  }

void Alien::tickReceived() {
    if((m_currentTick % ANIMATION_TICK_DECIMATION) == 0) {
        if(m_attack) {
            QPixmap map(":/pic/attack" + QString::number(m_stage) + ".png");
            QPixmap mapParent(800, 500);
            mapParent.fill(Qt::transparent);
            QPainter painter(&mapParent);
            painter.drawPixmap(QRectF(mapParent.width()-map.width(),500-map.height(), map.width(), map.height()), map.transformed(QTransform().scale(-1, 1)), QRectF(0,0, map.width(), map.height()));

            QPen pen = QColor("black");
            pen.setWidth(4);
            painter.setPen(pen);
            QRect rect(mapParent.width()-160, 0, 100, 10);
            QRect rectRemaining(mapParent.width()-160, 0, 100*(((double) (m_numAllowedHits - m_numHits))/m_numAllowedHits), 10);
            QBrush brush(QColor("red"));
            painter.fillRect(rectRemaining,brush);
            painter.drawRect(rect);


            QPen pen2 = QColor("black");
            pen2.setWidth(4);
            painter.setPen(pen2);
            QRect rect2(mapParent.width()-160, 20, 100, 10);
            QRect rectRemaining2(mapParent.width()-160, 20, 100*(((double) (m_numBullets))/m_maxNumBullets), 10);
            QBrush brush2(QColor("#9d00de"));
            painter.fillRect(rectRemaining2,brush2);
            painter.drawRect(rect2);



            setPixmap(mapParent);
            setMinimumWidth(mapParent.width());
            setMaximumWidth(mapParent.width());
            setMinimumHeight(mapParent.height());
            setMaximumHeight(mapParent.height());
            if(m_stage == 1)
                m_attack = false;
            m_stage= (m_stage == 1) ? 1 : (m_stage-1);
        } else if(m_hit) {
            QPixmap map(":/pic/hurt" + QString::number(m_stage) + ".png");
            QPixmap mapParent(800, 500);
            mapParent.fill(Qt::transparent);
            QPainter painter(&mapParent);
            painter.drawPixmap(QRectF(mapParent.width()-map.width(),500-map.height(), map.width(), map.height()), map.transformed(QTransform().scale(-1, 1)), QRectF(0,0, map.width(), map.height()));

            QPen pen = QColor("black");
            pen.setWidth(4);
            painter.setPen(pen);
            QRect rect(mapParent.width()-160, 0, 100, 10);
            QRect rectRemaining(mapParent.width()-160, 0, 100*(((double) (m_numAllowedHits - m_numHits))/m_numAllowedHits), 10);
            QBrush brush(QColor("red"));
            painter.fillRect(rectRemaining,brush);
            painter.drawRect(rect);





            QPen pen2 = QColor("black");
            pen2.setWidth(4);
            painter.setPen(pen2);
            QRect rect2(mapParent.width()-160, 20, 100, 10);
            QRect rectRemaining2(mapParent.width()-160, 20, 100*(((double) (m_numBullets))/m_maxNumBullets), 10);
            QBrush brush2(QColor("#9d00de"));
            painter.fillRect(rectRemaining2,brush2);
            painter.drawRect(rect2);







            setPixmap(mapParent);
            setMinimumWidth(mapParent.width());
            setMaximumWidth(mapParent.width());
            setMinimumHeight(mapParent.height());
            setMaximumHeight(mapParent.height());
            if(m_stage == 3)
                m_hit = false;
            m_stage= (m_stage == 3) ? 1 : (m_stage+1);
        } else if(m_alive) {
            QPixmap map(":/pic/idle" + QString::number(m_stage) + ".png");
            QPixmap mapParent(800, 500);
            mapParent.fill(Qt::transparent);
            QPainter painter(&mapParent);
            painter.drawPixmap(QRectF(mapParent.width()-map.width(),500-map.height(), map.width(), map.height()), map.transformed(QTransform().scale(-1, 1)), QRectF(0,0, map.width(), map.height()));

            QPen pen = QColor("black");
            pen.setWidth(4);
            painter.setPen(pen);
            QRect rect(mapParent.width()-160, 0, 100, 10);
            QRect rectRemaining(mapParent.width()-160, 0, 100*(((double) (m_numAllowedHits - m_numHits))/m_numAllowedHits), 10);
            QBrush brush(QColor("red"));
            painter.fillRect(rectRemaining,brush);
            painter.drawRect(rect);


            QPen pen2 = QColor("black");
            pen2.setWidth(4);
            painter.setPen(pen2);
            QRect rect2(mapParent.width()-160, 20, 100, 10);
            QRect rectRemaining2(mapParent.width()-160, 20, 100*(((double) (m_numBullets))/m_maxNumBullets), 10);
            QBrush brush2(QColor("#9d00de"));
            painter.fillRect(rectRemaining2,brush2);
            painter.drawRect(rect2);


            setPixmap(mapParent);
            setMinimumWidth(mapParent.width());
            setMaximumWidth(mapParent.width());
            setMinimumHeight(mapParent.height());
            setMaximumHeight(mapParent.height());
            if  ((rand() % 10) == 0) //only change state randomly, creating a random effect in the animation of the alien.
                m_stage= (m_stage == 3) ? 1 : (m_stage+1);
        } else if(m_dying) {
            QPixmap map(":/pic/dead" + QString::number(m_stage) + ".png");
            QPixmap mapParent(800, 500);
            mapParent.fill(Qt::transparent);
            QPainter painter(&mapParent);
            painter.drawPixmap(QRectF(mapParent.width()-map.width(),500-map.height(), map.width(), map.height()), map.transformed(QTransform().scale(-1, 1)), QRectF(0,0, map.width(), map.height()));
            setPixmap(mapParent);
            setMinimumWidth(mapParent.width());
            setMaximumWidth(mapParent.width());
            setMinimumHeight(mapParent.height());
            setMaximumHeight(mapParent.height());
            if(m_stage == 5)
                m_dying = false;
            m_stage= (m_stage == 5) ? 0 : (m_stage+1);
        } else {
            m_dead = true;
            emit alienDead();
            return;
        }
    }
    m_currentTick++;
    setGeometry(m_xPos, ZOMBIE_YPOS-90, width(), height());
    show();
}

void Alien::kill() {
    if(!m_dying && !m_dead) {
        m_stage = 1;
        m_alive = false;
        m_attack = false;
        m_hit = false;
        m_dying = true;
    }
}

bool Alien::isDead() {
    return m_dead;
}

void Alien::hit() {
    if(!m_dying && !m_dead) {
        m_hit = true;
        m_numHits++;
        m_stage = 1;
    }
}

void Alien::setNumAllowedHits(int numAllowedHits) {
    m_numAllowedHits = numAllowedHits;
}



void Alien::attack() {
    if(!m_dying && !m_dead) {
        m_attack = true;
        m_stage = 4;
        m_numBullets = (m_numBullets > 1) ? (m_numBullets-1) : 0;
    }
}

void Alien::increaseAmountOfBullets() {
    m_numBullets = (m_numBullets == m_maxNumBullets) ? m_maxNumBullets : (m_numBullets+1);
}

int Alien::getAmountOfBullets() {
    return m_numBullets;
}

void Alien::setMaximumBullets(int num) {
    m_maxNumBullets = num;
}

void Alien::resetAmountOfBullets() {
    m_numBullets = m_maxNumBullets;
}


