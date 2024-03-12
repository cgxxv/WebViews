#include "webengineview.h"

#include <QContextMenuEvent>

namespace Gpt {

WebEngineView::WebEngineView(QWidget *parent)
    : QWebEngineView{parent}
{

}

void WebEngineView::contextMenuEvent(QContextMenuEvent *event)
{
    event->ignore();
}

}
