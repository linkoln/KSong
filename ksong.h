#ifndef KSONG_H
#define KSONG_H

#include <QMainWindow>
#include <qaudio.h>
#include <qfile.h>
#include <qaudioinput.h>
#include <qaudiooutput.h>

namespace Ui {
class KSong;
}

class KSong : public QMainWindow
{
    Q_OBJECT

public:
    explicit KSong(QWidget *parent = 0);
    ~KSong();

private slots:
    void on_pushButton_clicked();

    void stopRecording();
    void handleStateChanged(QAudio::State newState);
    void handleStateChanged2(QAudio::State newState);

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::KSong *ui;

    QFile destinationFile;   // Class member
    QAudioInput* audio;

    QFile sourceFile;   // class member.
    QAudioOutput* audio2; // class member.
};

#endif // KSONG_H
