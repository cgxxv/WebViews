#ifndef WEBENGINEVIEW_H
#define WEBENGINEVIEW_H

#include <QtWebEngineWidgets/QWebEngineView>
#include <QWidget>

namespace Gpt {

class WebEngineView : public QWebEngineView
{
public:
    explicit WebEngineView(QWidget *parent = nullptr);

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;
};

}

#endif // WEBENGINEVIEW_H
