#include "soundplayer.h"
#include <QDebug>
#include <QThread>
extern char _binary_music_raw_start[];
extern char _binary_music_raw_end[];
extern char _binary_event_raw_start[];
extern char _binary_event_raw_end[];
extern char _binary_win_raw_start[];
extern char _binary_win_raw_end[];
extern char _binary_fail_raw_start[];
extern char _binary_fail_raw_end[];
SoundPlayer::SoundPlayer() {
    m_paError = Pa_Initialize();
    m_eventStream = nullptr;
    PaStreamParameters paStreamParameters;
    paStreamParameters.device = Pa_GetDefaultOutputDevice();
    paStreamParameters.channelCount = 1;
    paStreamParameters.sampleFormat = paInt16;
    paStreamParameters.suggestedLatency = Pa_GetDeviceInfo(paStreamParameters.device)->defaultLowOutputLatency;
    paStreamParameters.hostApiSpecificStreamInfo = nullptr;
    m_paError = Pa_OpenStream(&m_eventStream, nullptr, &paStreamParameters, SAMPLE_RATE, paFramesPerBufferUnspecified, paClipOff, nullptr, nullptr);
    if (m_paError != paNoError || ! m_eventStream) {
        Pa_Terminate();
    } else {
        m_paError = Pa_StartStream(m_eventStream);
        if (m_paError != paNoError) {
            Pa_Terminate();
        }
    }
}

SoundPlayer::~SoundPlayer() {
    m_paError = Pa_CloseStream(m_eventStream);
    if (m_paError != paNoError) {
        Pa_Terminate();
    }
}

void SoundPlayer::setEnableMusic(bool enableMusic) {
    m_enableMusic = enableMusic;
}

bool SoundPlayer::musicEnabled() {
    return m_enableMusic;
}
bool SoundPlayer::playMusic() {
    const double TRACK_DURATION = 134; //duration of the track in seconds.
    const int DURATION_BYTES = (int) (((double) (2*SAMPLE_RATE))*TRACK_DURATION); //factor 2 is due 16 bit sound.
    const int OFFSET = 0;
    PaError paError = Pa_Initialize();
    PaStream* stream = nullptr;
    PaStreamParameters paStreamParameters;
    paStreamParameters.device = Pa_GetDefaultOutputDevice();
    paStreamParameters.channelCount = 1;
    paStreamParameters.sampleFormat = paInt16;
    paStreamParameters.suggestedLatency = Pa_GetDeviceInfo(paStreamParameters.device)->defaultLowOutputLatency;
    paStreamParameters.hostApiSpecificStreamInfo = nullptr;
    paError = Pa_OpenStream(&stream, nullptr, &paStreamParameters, SAMPLE_RATE, paFramesPerBufferUnspecified, paClipOff, nullptr, nullptr);
    if (paError != paNoError || ! stream) {
        Pa_Terminate();
        return false;
    }
    paError = Pa_StartStream(stream);
    if (paError != paNoError) {
        Pa_Terminate();
        return false;
    }
    const size_t BUFFER_LEN = SAMPLE_RATE/10;
    int16_t data[BUFFER_LEN];
    while(true) {
        int index = 0;
        while(m_enableMusic && ((_binary_music_raw_start+index+OFFSET) < (_binary_music_raw_start+OFFSET+DURATION_BYTES))) {
            memcpy(data, _binary_music_raw_start+index+OFFSET, sizeof(data));
            paError = Pa_WriteStream(stream, data, BUFFER_LEN);
            if (paError != paNoError) {
                break;
            }
            memset(data, 0, sizeof(data));
            index = index + sizeof(data);
        }
        if(!m_enableMusic)
            QThread::msleep(500);
    }//TODO: get out of this loop and destroy the object when shutting down the software..
    paError = Pa_CloseStream(stream);
    if (paError != paNoError) {
        Pa_Terminate();
        return false;
    }
    Pa_Terminate();
    return true;
}

void SoundPlayer::interruptEventSound() {
    m_interruptEventSound = true;
}

bool SoundPlayer::playEventSound() {
    m_interruptEventSound = false;
    const double TRACK_DURATION = 0.6; //duration of the track in seconds.
    const int DURATION_BYTES = (int) (((double) (2*SAMPLE_RATE))*TRACK_DURATION); //factor 2 is due 16 bit sound.
    const int OFFSET = 0;
    const size_t BUFFER_LEN = SAMPLE_RATE/10;
    int16_t data[BUFFER_LEN];
    int index = 0;
    while(((_binary_event_raw_start+index+OFFSET) < (_binary_event_raw_start+OFFSET+DURATION_BYTES)) && !m_interruptEventSound) {
        memcpy(data, _binary_event_raw_start+index+OFFSET, sizeof(data));
        m_paError = Pa_WriteStream(m_eventStream, data, BUFFER_LEN);
        if (m_paError != paNoError) {
            break;
        }
        memset(data, 0, sizeof(data));
        index = index + sizeof(data);
    }
    return true;
}


bool SoundPlayer::playWinSound() {
    m_interruptEventSound = false;
    const double TRACK_DURATION = 1; //duration of the track in seconds.
    const int DURATION_BYTES = (int) (((double) (2*SAMPLE_RATE))*TRACK_DURATION); //factor 2 is due 16 bit sound.
    const int OFFSET = 0;
    const size_t BUFFER_LEN = SAMPLE_RATE/10;
    int16_t data[BUFFER_LEN];
    int index = 0;
    while(((_binary_win_raw_start+index+OFFSET) < (_binary_win_raw_start+OFFSET+DURATION_BYTES)) && !m_interruptEventSound) {
        memcpy(data, _binary_win_raw_start+index+OFFSET, sizeof(data));
        m_paError = Pa_WriteStream(m_eventStream, data, BUFFER_LEN);
        if (m_paError != paNoError) {
            break;
        }
        memset(data, 0, sizeof(data));
        index = index + sizeof(data);
    }
    return true;
}


bool SoundPlayer::playFailSound() {
    m_interruptEventSound = false;
    const double TRACK_DURATION = 1.65; //duration of the track in seconds.
    const int DURATION_BYTES = (int) (((double) (2*SAMPLE_RATE))*TRACK_DURATION); //factor 2 is due 16 bit sound.
    const int OFFSET = 0;
    const size_t BUFFER_LEN = SAMPLE_RATE/10;
    int16_t data[BUFFER_LEN];
    int index = 0;
    while(((_binary_fail_raw_start+index+OFFSET) < (_binary_fail_raw_start+OFFSET+DURATION_BYTES)) && !m_interruptEventSound) {
        memcpy(data, _binary_fail_raw_start+index+OFFSET, sizeof(data));
        m_paError = Pa_WriteStream(m_eventStream, data, BUFFER_LEN);
        if (m_paError != paNoError) {
            break;
        }
        memset(data, 0, sizeof(data));
        index = index + sizeof(data);
    }
    return true;
}
