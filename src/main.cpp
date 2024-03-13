#include "mainwindow.h"
#include "util_test.h"

#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[])
{
    Gpt::UtilTest test;
    QTest::qExec(&test, argc, argv);

    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/assets/ChatGPTs.svg"));

    MainWindow w;
    w.resize(1024, 768);
    w.show();

    return a.exec();
}
