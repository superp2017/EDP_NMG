#include "mainwindow.h"
#include <QApplication>
#include "testtcp.h"
#include "formcommunicationsystem.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    TestTCP w;
//    w.showNormal();
        MainWindow w;
        w.setMinimumSize(1100,940);
        w.showMaximized();
    return a.exec();
    return 0;
}
