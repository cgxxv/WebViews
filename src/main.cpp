#include "mainwindow.h"
#include "util_test.h"
#include "colorscheme.h"

#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[])
{
    Gpt::UtilTest test;
    QTest::qExec(&test, argc, argv);

#ifdef QT_DEBUG
    qputenv("QTWEBENGINE_REMOTE_DEBUGGING", "9999");
    qputenv("QTWEBENGINE_CHROMIUM_FLAGS", "--remote-debugging-port=9999");
#endif

    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/assets/ChatGPTs.svg"));

    auto colorScheme = new Gpt::ColorScheme(a.styleHints());

    MainWindow w(colorScheme);
    w.resize(1024, 768);
    w.show();

    return a.exec();
}
