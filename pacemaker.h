#ifndef PACEMAKER_H
#define PACEMAKER_H

#include <QObject>
#include <Qthread>
class PaceMaker : public QObject
{
    Q_OBJECT
public:
    explicit PaceMaker(QObject *parent = nullptr);

private:
    QThread* m_thread;
signals:
    void tick();
public slots:
    void start();
};

#endif // PACEMAKER_H
