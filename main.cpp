#include "ksong.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    KSong w;
    w.show();

    return a.exec();
}
