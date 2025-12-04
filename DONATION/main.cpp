#include "donacion.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Donacion w;
    w.show();
    return a.exec();
}
