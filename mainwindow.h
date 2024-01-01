#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<gamescene.h>
#include <QMap>
class Settings;
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
    void playWinSound();
    void playFailSound();
    void playEventSound();
    void restart();
signals:
    void tick();
    void notifyChar(char character);
    void gameEnded();
private slots:
    void toggleMusic();
    void updateTime();
    void updateScore();
    void alienDeadReceived();
    void clickSettings();

private:
    Ui::MainWindow *ui;
    int m_score;
    QMap<QThread*, SoundPlayer*> m_soundPlayers;
    qint64 m_startTime;
    bool m_gameRunning = true;
    Settings* m_settings = NULL;

protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
};

#endif // MAINWINDOW_H
