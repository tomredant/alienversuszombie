#include "mainwindow.h"
#include <QApplication>
#include<stdlib.h>
#include<time.h>
#include <QSplashScreen>
#include <QThread>
#include "pacemaker.h"

int main(int argc, char *argv[])
{

   //QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication a(argc, argv);

    srand((unsigned)time(NULL));
    QPixmap pixmap(":/pic/zombie1/Run2.png");
    QSplashScreen screen(pixmap);
    screen.show();
    for(int i=0;i<20;i++) {
        QThread::msleep(100);
        QApplication::processEvents();
    }
    screen.hide();
    MainWindow mainWindow;
    mainWindow.show();
    PaceMaker* paceMaker = new PaceMaker();
    QObject::connect(paceMaker,SIGNAL(tick()), &mainWindow, SLOT(tickReceived()));
    return a.exec();




}
