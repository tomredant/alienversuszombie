#ifndef SOUNDPLAYER_H
#define SOUNDPLAYER_H

#include <QObject>
#include <portaudio.h>

class SoundPlayer : public QObject
{
    Q_OBJECT
public:
    SoundPlayer();
    ~SoundPlayer();
    void interruptEventSound();
    void setEnableMusic(bool enableMusic);
    bool musicEnabled();
public slots:
    bool playMusic();
    bool playEventSound();
    bool playWinSound();
    bool playFailSound();

signals:

private:
    bool m_interruptEventSound = false;
    bool m_enableMusic = true;

    PaError m_paError;
    PaStream* m_eventStream;
    const int SAMPLE_RATE = 44100*2;


};

#endif // SOUNDPLAYER_H
