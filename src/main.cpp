#include "offsets.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Offsets w;
    w.show();

    return a.exec();
}
