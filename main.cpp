#include <QApplication>
#include <QtWebEngineWidgets/QWebEngineView>
#include <QUrl>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QWebEngineView view;
    view.setUrl(QUrl("https://chat.openai.com"));
    view.resize(1024, 768);
    view.show();

    return a.exec();
}
