#include <QApplication>
#include <QtWebEngineWidgets/QWebEngineView>
#include <QUrl>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/chatgpt.png"));

    QWebEngineView view;
    view.setUrl(QUrl("https://chat.openai.com"));
    view.resize(1024, 768);
    view.show();

    return a.exec();
}
