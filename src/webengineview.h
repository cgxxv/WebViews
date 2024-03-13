#ifndef WEBENGINEVIEW_H
#define WEBENGINEVIEW_H

#include <QtWebEngineWidgets/QWebEngineView>
#include <QWidget>
#include <QContextMenuEvent>

namespace Gpt {

class WebEngineView : public QWebEngineView
{
public:
    explicit WebEngineView(QWidget *parent = nullptr) : QWebEngineView{parent} {}

// protected:
//     void contextMenuEvent(QContextMenuEvent *event)
//     {
//         event->ignore();
//     }
};

}

#endif // WEBENGINEVIEW_H
