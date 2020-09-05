#include "ch9326debug.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CH9326DEBUG w;
    w.show();

    return a.exec();
}
