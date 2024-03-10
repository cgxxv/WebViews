#include "mainwindow.h"

#include <QApplication>
#include <QtWebEngineWidgets/QWebEngineView>
#include <QUrl>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/assets/gpt.png"));

    MainWindow w;
    w.resize(1024,768);
    w.show();

    //https://chat.openai.com
    //https://yiyan.baidu.com
    //https://tongyi.aliyun.com/qianwen
    //https://www.doubao.com

    // QWebEngineView view;
    // view.setUrl(QUrl("https://chat.openai.com"));
    // view.resize(1024, 768);
    // view.show();

    return a.exec();
}
