#include "View.h"
#include "Model.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    View view;
    view.show();
    return a.exec();
}
