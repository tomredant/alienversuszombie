#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<gamescene.h>
class SoundPlayer;
class QThread;
class QKeyEvent;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void clickAbout();
    void tickReceived();
signals:
    void tick();
    void notifyChar(char character);
    void gameEnded();
private slots:
    void toggleMusic();
    void updateTime();
    void updateScore();
    void alienDeadReceived();
private:
    Ui::MainWindow *ui;
    int m_score;
    SoundPlayer* m_player;
    QThread* m_musicThread;
    SoundPlayer* m_eventPlayer;
    QThread* m_eventMusicThread;
    qint64 m_startTime;
    bool m_gameRunning = true;

protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
};

#endif // MAINWINDOW_H
