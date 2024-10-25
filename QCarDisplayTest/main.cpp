#include "cardisp.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CarDisp w;
    w.show();

    return a.exec();
}
