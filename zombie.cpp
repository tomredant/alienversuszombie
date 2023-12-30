#include "zombie.h"
#include<QPixmap>
#include<QDebug>
#include<QCursor>
#include "gameproperties.h"
#include <QPainter>
Zombie::Zombie(QWidget* parent, int id): QLabel(parent)
{
    m_id = id;
    hide();
    m_xPos = -400;
    QString charString = ALLOWED_CHARACTERS.mid(rand() % (ALLOWED_CHARACTERS.length()), 1);
    m_character = charString.toLatin1().constData()[0];
    QFont font;
    m_currentTick = 0;
    setText(charString);
  }

void Zombie::tickReceived() {
    if((m_currentTick % ANIMATION_TICK_DECIMATION) == 0) {
        if(m_alive) {
            QPixmap map(":/pic/zombie" + QString::number(m_id) + "/Run" + QString::number(m_stage) + ".png");
            QPixmap mapParent(800, 500);
            mapParent.fill(Qt::transparent);
            QPainter painter(&mapParent);
            QFont font("Arial");
            font.setPointSize(FONT_SIZE);
            font.setBold(true);
            painter.setFont(font);
            painter.drawPixmap(QRectF(mapParent.width()/2-map.width()/2,410-map.height(), map.width(), map.height()), map, QRectF(0,0, map.width(), map.height()));
            QPen penText(QColor("#870011"));
            painter.setPen(penText);
            painter.drawText(QPoint(mapParent.width()/2, mapParent.height() - 0.5*FONT_SIZE), QString(QChar::fromLatin1(m_character)));
            setPixmap(mapParent);
            setMinimumWidth(mapParent.width());
            setMaximumWidth(mapParent.width());
            setMinimumHeight(mapParent.height());
            setMaximumHeight(mapParent.height());
            m_stage= (m_stage == 6) ? 1 : (m_stage+1);
        } else if(m_dying) {
            QPixmap map(":/pic/zombie" + QString::number(m_id) + "/Dead" + QString::number(m_stage) + ".png");
            QPixmap mapParent(800, 500);
            mapParent.fill(Qt::transparent);
            QPainter painter(&mapParent);
            QFont font("Arial");
            font.setPointSize(FONT_SIZE);
            font.setBold(true);
            painter.setFont(font);
            painter.drawPixmap(QRectF(mapParent.width()/2-100,410-map.height(), map.width(), map.height()), map, QRectF(0,0, map.width(), map.height()));
            QPen penText(QColor("#870011"));
            painter.setPen(penText);
            painter.drawText(QPoint(mapParent.width()/2, mapParent.height() - 0.5*FONT_SIZE), QString(QChar::fromLatin1(m_character)));
            setPixmap(mapParent);
            setMinimumWidth(mapParent.width());
            setMaximumWidth(mapParent.width());
            setMinimumHeight(mapParent.height());
            setMaximumHeight(mapParent.height());
            if(m_stage == 8)
                m_dying = false;
            m_stage= (m_stage == 8) ? 0 : (m_stage+1);
        } else if (m_attack) {
            QPixmap map(":/pic/zombie" + QString::number(m_id) + "/Attack" + QString::number(m_stage) + ".png");
            QPixmap mapParent(800, 500);
            mapParent.fill(Qt::transparent);
            QPainter painter(&mapParent);
            QFont font("Arial");
            font.setPointSize(FONT_SIZE);
            font.setBold(true);
            painter.setFont(font);
            painter.drawPixmap(QRectF(mapParent.width()/2-100,410-map.height(), map.width(), map.height()), map, QRectF(0,0, map.width(), map.height()));
            QPen penText(QColor("#870011"));
            painter.setPen(penText);
            painter.drawText(QPoint(mapParent.width()/2, mapParent.height() - 0.5*FONT_SIZE), QString(QChar::fromLatin1(m_character)));
            setPixmap(mapParent);
            setMinimumWidth(mapParent.width());
            setMaximumWidth(mapParent.width());
            setMinimumHeight(mapParent.height());
            setMaximumHeight(mapParent.height());
            if(m_stage == 6)
                m_attack = false;
            m_stage= (m_stage == 6) ? 0 : (m_stage+1);
        } else {
            m_dead = true;
            hide();
            return;
        }
    }
    m_currentTick++;
    setGeometry(m_xPos, ZOMBIE_YPOS, width(), height());
    if(m_alive)
        m_xPos = m_xPos + ZOMBIE_STEP_SIZE;
    show();
}

char Zombie::getCharacter() {
    return m_character;
}

int Zombie::getPosition() {
    return m_xPos;
}

void Zombie::attack() {
    m_alive = false;
    m_dying = false;
    m_attack = true;
    m_stage = 1;
}

void Zombie::kill() {
    if(m_alive) {
        m_alive = false;
        m_dying = true;
        m_stage = 1;
    }
}

bool Zombie::isDead() {
    return m_dead;
}

bool Zombie::isAlive() {
    return m_alive;
}

