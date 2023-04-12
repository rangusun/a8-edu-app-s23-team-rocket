
#include "FireworkSim.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FireworkSim w;
    w.show();
    return a.exec();
}
