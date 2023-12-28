#include "alien.h"
#include<QPixmap>
#include<QDebug>
#include<QCursor>
#include "gameproperties.h"
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
            painter.drawPixmap(QRectF(mapParent.width()-map.width(),450-map.height(), map.width(), map.height()), map.transformed(QTransform().scale(-1, 1)), QRectF(0,0, map.width(), map.height()));
            setPixmap(mapParent);
            setMinimumWidth(mapParent.width());
            setMaximumWidth(mapParent.width());
            setMinimumHeight(mapParent.height());
            setMaximumHeight(mapParent.height());
            if(m_stage == 4)
                m_attack = false;
            m_stage= (m_stage == 4) ? 1 : (m_stage+1);
        } else if(m_hit) {
            QPixmap map(":/pic/hurt" + QString::number(m_stage) + ".png");
            QPixmap mapParent(800, 500);
            mapParent.fill(Qt::transparent);
            QPainter painter(&mapParent);
            painter.drawPixmap(QRectF(mapParent.width()-map.width(),450-map.height(), map.width(), map.height()), map.transformed(QTransform().scale(-1, 1)), QRectF(0,0, map.width(), map.height()));
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
            //QFont font("Arial");
            //font.setPointSize(FONT_SIZE);
            //font.setBold(true);
            //painter.setFont(font);
            painter.drawPixmap(QRectF(mapParent.width()-map.width(),450-map.height(), map.width(), map.height()), map.transformed(QTransform().scale(-1, 1)), QRectF(0,0, map.width(), map.height()));
            //QPen penText(QColor("#00e0fc"));
            //painter.setPen(penText);
            //painter.drawText(QPoint(mapParent.width()/3, mapParent.height() - 0.5*FONT_SIZE), QString(QChar::fromLatin1('')).toUpper());
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
            //QFont font("Arial");
            //font.setPointSize(FONT_SIZE);
            //font.setBold(true);
            //painter.setFont(font);
            painter.drawPixmap(QRectF(mapParent.width()-map.width(),450-map.height(), map.width(), map.height()), map.transformed(QTransform().scale(-1, 1)), QRectF(0,0, map.width(), map.height()));
            //QPen penText(QColor("#00e0fc"));
            //painter.setPen(penText);
            //painter.drawText(QPoint(mapParent.width()/3, mapParent.height() - 0.5*FONT_SIZE), QString(QChar::fromLatin1('')).toUpper());
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
    setGeometry(m_xPos, ZOMBIE_YPOS-40, width(), height());
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
    if(!m_dying || m_dead) {
        m_hit = true;
        m_stage = 1;
    }
}



void Alien::attack() {
    if(!m_dying || m_dead) {
        m_attack = true;
        m_stage = 1;
    }
}


