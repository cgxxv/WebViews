#ifndef COLORSCHEME_H
#define COLORSCHEME_H

#include <QApplication>
#include <QStyleHints>
#include <QObject>
#include <QDebug>
#include <QPalette>

namespace Gpt
{

class ColorScheme : public QObject
{
    Q_OBJECT
public:
    explicit ColorScheme(QStyleHints *styleHints, QObject *parent = nullptr) : QObject(parent)
    {
        connect(styleHints, &QStyleHints::colorSchemeChanged, this, &ColorScheme::handleChanged);
        m_scheme = styleHints->colorScheme();
    }

    bool isDarkMode()
    {
        return m_scheme == Qt::ColorScheme::Dark;
    }

    bool isLightMode()
    {
        return m_scheme == Qt::ColorScheme::Light;
    }

private slots:
    void handleChanged(Qt::ColorScheme colorScheme)
    {
        m_scheme = colorScheme;
        if (colorScheme == Qt::ColorScheme::Dark) {
            qDebug() << "暗色主题";
        } else if (colorScheme == Qt::ColorScheme::Light) {
            qDebug() << "亮色主题";
        } else {
            qDebug() << "未知主题";
        }
    }

private:
    Qt::ColorScheme m_scheme;
};

}

#endif // COLORSCHEME_H
