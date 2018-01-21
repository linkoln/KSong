#include "ksong.h"
#include "ui_ksong.h"

#include <qdebug.h>
#include <qtimer.h>

KSong::KSong(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::KSong)
{
    ui->setupUi(this);
}

KSong::~KSong()
{
    delete ui;
}

void KSong::on_pushButton_clicked()
{
    destinationFile.setFileName("/Users/lqlin/Desktop/test.raw");
    destinationFile.open( QIODevice::WriteOnly | QIODevice::Truncate );

    QAudioFormat format;
    // Set up the desired format, for example:
    format.setSampleRate(8000);
    format.setChannelCount(1);
    format.setSampleSize(8);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::UnSignedInt);

    QAudioDeviceInfo info = QAudioDeviceInfo::defaultInputDevice();
    if (!info.isFormatSupported(format)) {
        qWarning() << "Default format not supported, trying to use the nearest.";
        format = info.nearestFormat(format);
    }

    audio = new QAudioInput(format, this);
    connect(audio, SIGNAL(stateChanged(QAudio::State)), this, SLOT(handleStateChanged(QAudio::State)));

//    QTimer::singleShot(3000, this, SLOT(stopRecording()));
    audio->start(&destinationFile);
    // Records audio for 3000ms
}

void KSong::stopRecording()
{
    audio->stop();
    destinationFile.close();
    delete audio;
}

void KSong::handleStateChanged(QAudio::State newState)
{
    switch (newState) {
    case QAudio::StoppedState:
        if (audio->error() != QAudio::NoError) {
            // Error handling
        } else {
            // Finished recording
        }
        break;

    case QAudio::ActiveState:
        // Started recording - read from IO device
        break;

    default:
        // ... other cases as appropriate
        break;
    }
}

void KSong::on_pushButton_2_clicked()
{
//    if (audio->state() == QAudio::ActiveState) {
//        audio->stop();
//    }

    sourceFile.setFileName("/Users/lqlin/Desktop/test.raw");
    sourceFile.open(QIODevice::ReadOnly);

    QAudioFormat format;
    // Set up the format, eg.
    format.setSampleRate(8000);
    format.setChannelCount(1);
    format.setSampleSize(8);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::UnSignedInt);

    QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
    if (!info.isFormatSupported(format)) {
        qWarning() << "Raw audio format not supported by backend, cannot play audio.";
        return;
    }

    audio2 = new QAudioOutput(format, this);
    connect(audio2, SIGNAL(stateChanged(QAudio::State)), this, SLOT(handleStateChanged2(QAudio::State)));
    audio2->start(&sourceFile);
}

void KSong::handleStateChanged2(QAudio::State newState)
{
    switch (newState) {
    case QAudio::IdleState:
        // Finished playing (no more data)
        audio2->stop();
        sourceFile.close();
        delete audio2;
        break;

    case QAudio::StoppedState:
        // Stopped for other reasons
        if (audio2->error() != QAudio::NoError) {
            // Error handling
        }
        break;

    default:
        // ... other cases as appropriate
        break;
    }
}

void KSong::on_pushButton_3_clicked()
{
    if (audio->state() == QAudio::ActiveState) {
        audio->stop();
        destinationFile.close();
        delete audio;
    }
}
