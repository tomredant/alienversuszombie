#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>
#include "soundplayer.h"
#include "showlicense.h"
#include <QKeyEvent>
#include <QDebug>
#include <QDateTime>
#include <settings.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QList<QToolBar *> allToolBars = findChildren<QToolBar *>();
    foreach(QToolBar *tb, allToolBars) {
        removeToolBar(tb);
        delete tb;
    }



    const int NUM_SOUND_PLAYERS = 10;
    for(int i=0;i<NUM_SOUND_PLAYERS;i++) {
        QThread* thread = new QThread();
        SoundPlayer* player = new SoundPlayer();
        m_soundPlayers.insert(thread, player);
        thread->setObjectName("Audio player thread " + QString::number(i));
        thread->start();
        player->moveToThread(thread);
    }
    m_soundPlayers.first()->setBusy();
    QMetaObject::invokeMethod(m_soundPlayers.first(), "playMusic"); // the first player plays the music.

    connect(ui->gameScene, SIGNAL(updateScore()), this, SLOT(playWinSound()));
    connect(ui->gameScene, SIGNAL(alienHit()), this, SLOT(playFailSound()));
    connect(ui->gameScene, SIGNAL(alienAttack()), this, SLOT(playEventSound()));

    connect(this, SIGNAL(tick()), ui->gameScene, SLOT(tickReceived()));
    connect(this, SIGNAL(notifyChar(char)), ui->gameScene, SLOT(charNotified(char)));
    connect(ui->gameScene, SIGNAL(updateScore()), this, SLOT(updateScore()));

    connect(ui->gameScene, SIGNAL(alienDead()), this, SLOT(alienDeadReceived()));
    setStyleSheet("QGraphicsView { background: rgb(120, 92, 98);border:0px }");
    setStyleSheet("QMainWindow { background: rgb(120, 92, 98);}");

    ui->gridLayout->setMargin(0);
    ui->statusBar->hide();


    connect(ui->muteButton,SIGNAL(clicked()), this, SLOT(toggleMusic()));
    connect(ui->aboutButton,SIGNAL(clicked()), this, SLOT(clickAbout()));
    connect(ui->settingsButton,SIGNAL(clicked()), this, SLOT(clickSettings()));


    m_score=0;
    ui->score->setText("<font color=\"#870011\">" + QString::number(m_score) + "</font>");
    ui->time->setText("<font color=\"#870011\">" + QString::number(0) + "</font>");

    connect(ui->restartButton,SIGNAL(clicked()), this, SLOT(restart()));
    m_startTime = QDateTime::currentMSecsSinceEpoch();
}



void MainWindow::restart() {
    m_score=0;
    ui->score->setText("<font color=\"#870011\">" + QString::number(m_score) + "</font>");
    GameScene* gameScene = new GameScene();
    gameScene->setMaximumWidth(1700);
    gameScene->setMaximumHeight(956);
    gameScene->setMinimumWidth(1700);
    gameScene->setMinimumHeight(956);
    GameScene* oldScene = ui->gameScene;
    ui->gridLayout->replaceWidget(ui->gameScene, gameScene);
    delete oldScene;
    ui->gameScene = gameScene;
    connect(this, SIGNAL(tick()), gameScene, SLOT(tickReceived()));
    connect(this, SIGNAL(notifyChar(char)), gameScene, SLOT(charNotified(char)));
    connect(ui->gameScene, SIGNAL(updateScore()), this, SLOT(updateScore()));
    connect(ui->gameScene, SIGNAL(updateScore()), this, SLOT(playWinSound()));
    connect(ui->gameScene, SIGNAL(alienHit()), this, SLOT(playFailSound()));
    connect(ui->gameScene, SIGNAL(alienAttack()), this, SLOT(playEventSound()));
    connect(ui->gameScene, SIGNAL(alienDead()), this, SLOT(alienDeadReceived()));
    m_startTime = QDateTime::currentMSecsSinceEpoch();
    m_gameRunning = true;
 }

void MainWindow::alienDeadReceived() {
    emit gameEnded();
    m_gameRunning = false;
}
void MainWindow::updateTime() {
    qint64 currentTime = QDateTime::currentMSecsSinceEpoch();
    ui->time->setText("<font color=\"#870011\">" + QString::number((int)((currentTime-m_startTime)/1000)) + "</font>");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateScore(){
    (m_score)++;
    ui->score->setText("<font color=\"#870011\">" + QString::number(m_score) + "</font>");
}


void MainWindow::toggleMusic() {
    m_soundPlayers.first()->setEnableMusic(!m_soundPlayers.first()->musicEnabled());
    if(m_soundPlayers.first()->musicEnabled())
        ui->muteButton->setIcon(QIcon(":/pic/icon_sound.png"));
    else
        ui->muteButton->setIcon(QIcon(":/pic/icon_mute.png"));

}

void MainWindow::clickSettings() {
    if(m_settings == NULL) {
        m_settings = new Settings();
        connect(m_settings,SIGNAL(restart()), this, SLOT(restart()));
    }
    m_settings->show();
    m_settings->raise();
}

void MainWindow::clickAbout() {
    std::vector<std::string> libs;
    libs.push_back("AlienVersuszombie#" + QObject::tr("Game developed by Tom Redant, \nSource Code:\nhttps://github.com/tomredant/alienversuszombie").toStdString() + "#gpl-3.0");
    libs.push_back(R"MYSTRING(PortAudio V19.6.0-devel##/*
                  * PortAudio Portable Real-Time Audio Library
                  * Latest Version at: http://www.portaudio.com
                  *
                  * Copyright (c) 1999-2008 Phil Burk and Ross Bencina
                  *
                  * Permission is hereby granted, free of charge, to any person obtaining
                  * a copy of this software and associated documentation files
                  * (the "Software"), to deal in the Software without restriction,
                  * including without limitation the rights to use, copy, modify, merge,
                  * publish, distribute, sublicense, and/or sell copies of the Software,
                  * and to permit persons to whom the Software is furnished to do so,
                  * subject to the following conditions:
                  *
                  * The above copyright notice and this permission notice shall be
                  * included in all copies or substantial portions of the Software.
                  *
                  * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
                  * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
                  * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
                  * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR
                  * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
                  * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
                  * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
                  */

                 /*
                  * The text above constitutes the entire PortAudio license; however,
                  * the PortAudio community also makes the following non-binding requests:
                  *
                  * Any person wishing to distribute modifications to the Software is
                  * requested to send the modifications to the original developer so that
                  * they can be incorporated into the canonical version. It is also
                  * requested that these non-binding requests be included along with the
                  * license above.
                  */


                 PortAudio is a portable audio I/O library designed for cross-platform
                 support of audio. It uses either a callback mechanism to request audio
                 processing, or blocking read/write calls to buffer data between the
                 native audio subsystem and the client. Audio can be processed in various
                 formats, including 32 bit floating point, and will be converted to the
                 native format internally.
)MYSTRING");
    libs.push_back("Qt5.15.3#Source files can be obtained from http://www.qt.io.#lgpl-3.0");
    libs.push_back("MinGW-W64-builds-4.3.5##MinGW-w64");
    libs.push_back("libstdc++-6##gpl-3.0_runtime_exception");
    libs.push_back(R"MYSTRING(Artwork and Audio##
Artwork obtained from:
                   https://craftpix.net/freebies/2d-game-zombie-character-free-sprite-pack-1/
                   https://craftpix.net/freebies/2d-game-alien-character-free-sprite/
                   https://craftpix.net/freebies/free-halloween-2d-game-backgrounds/
                   These items are available for use on a royalty free basis in unlimited projects. License details are shown on the link below:
                   https://craftpix.net/file-licenses/



Audio obtained from:
                   https://freesound.org/people/AtoMediaDesign/sounds/648969/
                   By AtoMediaDesign
                   CC BY 4.0 DEED
                   Attribution 4.0 International
                   https://creativecommons.org/licenses/by/4.0/

                   https://freesound.org/people/UNIVERSFIELD/sounds/706326/
                   by UNIVERSFIELD
                   CC BY 4.0 DEED
                   Attribution 4.0 International
                   https://creativecommons.org/licenses/by/4.0/

                   https://freesound.org/people/Bird_man/sounds/317136/
                   by Bird_man
                   CC0 1.0 DEED
                   CC0 1.0 Universal
                   https://creativecommons.org/publicdomain/zero/1.0/

                   https://freesound.org/people/CrocyTC/sounds/353062/
                   by CrocyTC
                   CC0 1.0 DEED
                   CC0 1.0 Universal
                   https://creativecommons.org/publicdomain/zero/1.0/
)MYSTRING");

    populateLicenseDialog(libs);
    setCustomLicenseMainMessage("This game was made possible by the existence of few third-party libraries and resources, which are used in this game. A complete list is shown in the tabs below.");
    setCustomLicenseLogo(":/pic/alienversuszombie.ico");
    setCustomLicenseAcceptText("Accept");
    setCustomLicenseRejectText("Reject");
    setCustomLicenseWindowTitleText("About");
    showLicenseDialog();
    if(!waitLicenseDialogAccepted())
        return;
}



void MainWindow::tickReceived() {
    if(m_gameRunning) {
        updateTime();
        emit tick();
    }
}




void MainWindow::keyPressEvent(QKeyEvent *ev)
{
    if(ev->text().size() > 0) {
        char character = ev->text().toLatin1().constData()[0];
        emit notifyChar(character);
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *ev)
{
    Q_UNUSED(ev);
}


void MainWindow::playEventSound() {
    QList<SoundPlayer*> players = m_soundPlayers.values();
    for(int i=0;i<players.size();i++) {
        if(!players[i]->isBusy()) {
            players[i]->setBusy();
            QMetaObject::invokeMethod(players[i], "playEventSound");
            break;
        }
    }
}

void MainWindow::playFailSound() {
    QList<SoundPlayer*> players = m_soundPlayers.values();
    for(int i=0;i<players.size();i++) {
        if(!players[i]->isBusy()) {
            players[i]->setBusy();
            QMetaObject::invokeMethod(players[i], "playFailSound");
            break;
        }
    }
}

void MainWindow::playWinSound() {
    QList<SoundPlayer*> players = m_soundPlayers.values();
    for(int i=0;i<players.size();i++) {
        if(!players[i]->isBusy()) {
            players[i]->setBusy();
            QMetaObject::invokeMethod(players[i], "playWinSound");
            break;
        }
    }
}
