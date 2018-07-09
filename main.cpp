#include "mainwindow.h"
#include <QApplication>
#include<QStyleFactory>
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(true);
    a.setApplicationName( QString("ChatSatov") );
    a.setStyle("gtk");
    MainWindow w;
    w.show();
    return a.exec();
}
