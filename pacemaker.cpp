#include "pacemaker.h"
#include "gameproperties.h"
#include <Qthread>
PaceMaker::PaceMaker(QObject *parent) : QObject(parent)
{

    m_thread = new QThread();
    m_thread->start();
    moveToThread(m_thread);
    QMetaObject::invokeMethod(this, "start");

}


void PaceMaker::start() {
    while(true) {
        emit tick();
        QThread::msleep(GAME_TICK_MS);
    }
}
