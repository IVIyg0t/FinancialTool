#include "acctmgr.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AcctMgr w;
    w.show();

    return a.exec();
}
