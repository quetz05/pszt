#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    for (int i = 0; i < 2; ++i) {
        //do nothing
        while(1);
    }
    
    return a.exec();
}
