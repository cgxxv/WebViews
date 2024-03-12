#ifndef COOKIEMANAGER_H
#define COOKIEMANAGER_H

#include <QObject>
#include <QNetworkCookie>
#include <QWebEngineCookieStore>
#include <QString>
#include <QMap>
#include <QList>

namespace Gpt
{

class CookieManager : public QObject
{
    Q_OBJECT
public:
    explicit CookieManager(QWebEngineCookieStore *cookieStore, QObject *parent = nullptr);
    ~CookieManager();

    void setCookieFilePath(const QString &cookieFilePath);
    void saveAllCookies();
    void loadCookies();

private slots:
    void on_cookie_added(const QNetworkCookie &cookie);
    void on_cookie_removed(const QNetworkCookie &cookie);

private:
    QWebEngineCookieStore *m_cookieStore;
    QString m_cookieFilepath;
    QMap<QString, QList<QNetworkCookie>> m_cookies;
};

}

#endif // COOKIEMANAGER_H
