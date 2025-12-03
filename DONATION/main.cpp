#include "donacion.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Donacion w;   // Clase Donacion, no donacion
    w.show();

    return a.exec();
}
