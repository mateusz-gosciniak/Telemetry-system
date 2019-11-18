#include "klasaglowna.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    klasaglowna w;
    w.show();

    return a.exec();
}
