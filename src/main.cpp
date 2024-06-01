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

    auto view = new Gpt::WebEngineView;
    auto colorScheme = new Gpt::ColorScheme(a.styleHints(), view);

    MainWindow w(colorScheme, view);
    w.resize(1280, 768);
    w.show();

    return a.exec();
}
