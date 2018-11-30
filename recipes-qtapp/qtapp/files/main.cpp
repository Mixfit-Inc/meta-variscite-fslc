// Author: Roberto Bellinato roberto.bellinato@egicon.com

#include "mainwindow.h"
#include <QApplication>
#include <bytedatarappresentation.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.showMaximized();
    //w.show();

    return a.exec();
}
