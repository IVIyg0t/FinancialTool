#include "fintool.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FinTool w;
    w.show();

    return a.exec();
}
