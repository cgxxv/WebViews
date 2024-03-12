#include "mainwindow.h"

#include <QApplication>
#include <QIcon>
#include <QPixmap>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setWindowIcon(QIcon(":/assets/ChatGPTs.svg"));

    MainWindow w;
    w.resize(1024,768);
    w.show();

    return a.exec();
}
