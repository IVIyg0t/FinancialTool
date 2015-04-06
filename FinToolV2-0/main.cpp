#include "fintool.h"
#include "login.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login l;

    if(l.exec() == QDialog::Accepted){

        FinTool w(l.getUsername());
        w.setUsername(l.getUsername());
        w.setPassword(l.getPassword());
        w.show();
        return a.exec();
    }
    else{
        l.close();
        return 0;
    }

}
