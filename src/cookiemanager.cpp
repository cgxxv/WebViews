#include "cookiemanager.h"

#include <QFile>
#include <QDataStream>
#include <QIODevice>
#include <QWebEngineCookieStore>
#include <QDebug>

namespace Gpt
{

CookieManager::CookieManager(QWebEngineCookieStore *cookieStore, QObject *parent)
    : QObject(parent)
    , m_cookieStore(cookieStore)
{
    // Connect signals to handle cookie changes
    connect(cookieStore, &QWebEngineCookieStore::cookieAdded, this, &CookieManager::on_cookie_added);
    connect(cookieStore, &QWebEngineCookieStore::cookieRemoved, this, &CookieManager::on_cookie_removed);

    // Load cookies from file
    // load_cookies();
}

CookieManager::~CookieManager()
{
    saveAllCookies();
    // delete m_cookie_store;
}

void CookieManager::setCookieFilePath(const QString &cookieFilePath)
{
    // TODO: need a lock for doing this?
    m_cookieFilepath = cookieFilePath;
}

void CookieManager::saveAllCookies()
{
    for (const auto &key : m_cookies.keys()) {
        qDebug() << ">>>>>>>>>>>>>>>>>> store cookie file: " + key + ">>>>>>>>>>>>>>>>>>";

        // Save cookies to file
        QFile file(key);
        if (file.open(QIODevice::WriteOnly)) {
            QDataStream out(&file);
            auto cookies = m_cookies.value(key);
            out << cookies.size(); // Write the number of cookies
            qDebug() << "Store cookie size: " << cookies.size();
            for (const auto &cookie : qAsConst(cookies)) {
                qDebug() << "Store cookie: " << cookie;
                out << cookie.toRawForm(); // Write the cookie in raw form
            }
        }

        qDebug() << "<<<<<<<<<<<<<<<<<< store cookie file: " + key + "<<<<<<<<<<<<<<<<<<";
    }
}

void CookieManager::loadCookies()
{
    qDebug() << ">>>>>>>>>>>>>>>>>> restore cookie file: " + m_cookieFilepath + ">>>>>>>>>>>>>>>>>>";

    // Load cookies from file
    QFile file(m_cookieFilepath);
    if (file.open(QIODevice::ReadOnly)) {
        QDataStream in(&file);
        int cookieCount;
        in >> cookieCount; // Read the number of cookies
        qDebug() << "Recover cookie size: " << cookieCount;
        for (int i = 0; i < cookieCount; ++i) {
            QByteArray rawCookie;
            in >> rawCookie; // Read the raw cookie data
            QNetworkCookie cookie = QNetworkCookie::parseCookies(rawCookie).first(); // Parse the raw cookie
            qDebug() << "Recover cookie: " << cookie;
            m_cookieStore->setCookie(cookie); // Set the cookie to the page
        }
    }

    qDebug() << "<<<<<<<<<<<<<<<<<< restore cookie file: " + m_cookieFilepath + "<<<<<<<<<<<<<<<<<<";
}

void CookieManager::on_cookie_added(const QNetworkCookie &cookie)
{
    qDebug() << "Added cookie: " << cookie;

    QList<QNetworkCookie> cookies = m_cookies.value(m_cookieFilepath);
    cookies.append(cookie);
    m_cookies.insert(m_cookieFilepath, cookies);
}

void CookieManager::on_cookie_removed(const QNetworkCookie &cookie)
{
    qDebug() << "Removed cookie: " << cookie;

    QList<QNetworkCookie> cookies = m_cookies.value(m_cookieFilepath);
    cookies.removeAll(cookie);
    m_cookies.insert(m_cookieFilepath, cookies);
}

}
