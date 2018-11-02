#include "lifewindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LifeWindow w;
    w.show();

    return a.exec();
}
