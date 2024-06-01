#include "colorscheme.h"

#include <QApplication>
#include <QStyleHints>
#include <QDebug>
#include <QPalette>
#include <QString>

namespace Gpt
{

ColorScheme::ColorScheme(QStyleHints *styleHints, WebEngineView *view, QObject *parent)
    : QObject(parent)
    , m_scheme(styleHints->colorScheme())
    , view(view)
    , m_gpt(GPT_CHATGPT)
{
    connect(styleHints, &QStyleHints::colorSchemeChanged, this, &ColorScheme::handleChanged);
}

bool ColorScheme::isDarkMode()
{
    return QApplication::styleHints()->colorScheme() == Qt::ColorScheme::Dark;
}

bool ColorScheme::isLightMode()
{
    return QApplication::styleHints()->colorScheme() == Qt::ColorScheme::Light;
}

void ColorScheme::setCurrentGpt(qint8 gpt)
{
    m_gpt = gpt;
}

QString ColorScheme::getDarkModeScript()
{
    if (m_gpt == GPT_CHATGPT) {
        return R"(
            document.documentElement.style.colorScheme = 'dark';
            document.documentElement.className = 'dark';
        )";
    } else {
        return "";
        // return R"(
        //     document.documentElement.style.background = '#212121';
        //     document.documentElement.style.backgroundColor = '#212121';
        //     document.documentElement.style.color = '#ffffff';
        //     document.body.style.background = '#212121';
        //     document.body.style.backgroundColor = '#212121';
        //     document.body.style.color = '#ffffff';
        // )";
    }
}

QString ColorScheme::getLightModeScript()
{
    if (m_gpt == GPT_CHATGPT) {
        return R"(
            document.documentElement.style.colorScheme = 'light';
            document.documentElement.className = 'light';
        )";
    } else {
        return "";
        // return R"(
        //     document.documentElement.style.background = '#ffffff';
        //     document.documentElement.style.backgroundColor = '#ffffff';
        //     document.documentElement.style.color = '#000000';
        //     document.body.style.background = '#ffffff';
        //     document.body.style.backgroundColor = '#ffffff';
        //     document.body.style.color = '#000000';
        // )";
    }
}

void ColorScheme::handleChanged(Qt::ColorScheme colorScheme)
{
    m_scheme = colorScheme;

    if (!view) {
        qDebug() << "Uninitialized web view";
        return;
    }

    if (m_scheme == Qt::ColorScheme::Dark) {
        qDebug() << "switching to dark mode";
        view->page()->runJavaScript(getDarkModeScript());
    } else {
        qDebug() << "switching to light mode";
        view->page()->runJavaScript(getLightModeScript());
    }
}

};
