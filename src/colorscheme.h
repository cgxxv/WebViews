#ifndef COLORSCHEME_H
#define COLORSCHEME_H

#include "webengineview.h"

#include <QStyleHints>
#include <QObject>

#define GPT_CHATGPT 0
#define GPT_YIYAN 1
#define GPT_TONGYI 2
#define GPT_DOUBAO 3

namespace Gpt
{

class ColorScheme : public QObject
{
    Q_OBJECT
public:
    explicit ColorScheme(QStyleHints *styleHints, WebEngineView *view, QObject *parent = nullptr);

    bool isDarkMode();
    bool isLightMode();
    void setCurrentGpt(qint8 current);
    QString getDarkModeScript();
    QString getLightModeScript();

private slots:
    void handleChanged(Qt::ColorScheme colorScheme);

private:
    Qt::ColorScheme m_scheme;
    qint8 m_gpt;
    WebEngineView *view;
};

}

#endif // COLORSCHEME_H
