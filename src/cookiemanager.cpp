#include "cookiemanager.h"
#include "util.h"

#include <QFile>
#include <QDataStream>
#include <QIODevice>
#include <QWebEngineCookieStore>
#include <QStandardPaths>
#include <QDebug>

#define SECRET_KEY "Your Secret Key"

namespace Gpt
{

CookieManager::CookieManager(QWebEngineCookieStore *cookieStore, QObject *parent)
    : QObject(parent)
    , m_cookieStore(cookieStore)
{
    // Connect signals to handle cookie changes
    connect(cookieStore, &QWebEngineCookieStore::cookieAdded, this, &CookieManager::on_cookie_added);
    connect(cookieStore, &QWebEngineCookieStore::cookieRemoved, this, &CookieManager::on_cookie_removed);

#ifdef Q_OS_WIN
    // Windows: Set the cookie path to %LOCALAPPDATA%/YourAppName
    QString cookieDir = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) + "/ChatGPTs";
#elif defined(Q_OS_MACOS)
    // macOS: Set the cookie path to ~/Library/Application Support/YourAppName
    QString cookieDir = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) + "/ChatGPTs";
#elif defined(Q_OS_LINUX)
    // Linux: Set the cookie path to ~/.local/share/YourAppName
    QString cookieDir = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) + "/ChatGPTs";
#else
    // Default: Set the cookie path to a generic directory
    QString cookieDir = QDir::homePath() + "/.cache/ChatGPTs";
#endif
    m_cookieDir = cookieDir;
}

CookieManager::~CookieManager()
{
    saveAllCookies();
}

void CookieManager::setCookieFile(const QString &url)
{
    QString hashedUrl = QString::fromLatin1(url.toUtf8().toHex());
    QString cookieFile = m_cookieDir+"/"+hashedUrl+".cookies.dat";
    qInfo() << "url: " << url << ", Cookie file: " << cookieFile;

    // TODO: need a lock for doing this?
    m_cookieFile = cookieFile;
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
                QByteArray encryptedCookie = Util::encryptData(cookie.toRawForm(), SECRET_KEY);
                if (nullptr == encryptedCookie) continue;
                // Write the encrypted cookie in raw form
                out << encryptedCookie;
            }
        }

        qDebug() << "<<<<<<<<<<<<<<<<<< store cookie file: " + key + "<<<<<<<<<<<<<<<<<<";
    }
}

void CookieManager::loadCookies()
{
    qDebug() << ">>>>>>>>>>>>>>>>>> restore cookie file: " + m_cookieFile + ">>>>>>>>>>>>>>>>>>";

    // Load cookies from file
    QFile file(m_cookieFile);
    if (file.open(QIODevice::ReadOnly)) {
        QDataStream in(&file);
        qsizetype cookieCount;
        in >> cookieCount; // Read the number of cookies
        qDebug() << "Recover cookie size: " << cookieCount;
        for (int i = 0; i < cookieCount; ++i) {
            QByteArray rawCookie, encryptedCookie;
            in >> encryptedCookie; // Read the raw cookie data
            rawCookie = Util::decryptData(encryptedCookie, SECRET_KEY);
            if (nullptr == rawCookie) continue;
            QNetworkCookie cookie = QNetworkCookie::parseCookies(rawCookie).first(); // Parse the raw cookie
            qDebug() << "Recover cookie: " << cookie;
            m_cookieStore->setCookie(cookie); // Set the cookie to the page
        }
    }

    qDebug() << "<<<<<<<<<<<<<<<<<< restore cookie file: " + m_cookieFile + "<<<<<<<<<<<<<<<<<<";
}

void CookieManager::on_cookie_added(const QNetworkCookie &cookie)
{
    // qDebug() << "Added cookie: " << cookie;

    QList<QNetworkCookie> cookies = m_cookies.value(m_cookieFile);
    cookies.append(cookie);
    m_cookies.insert(m_cookieFile, cookies);
}

void CookieManager::on_cookie_removed(const QNetworkCookie &cookie)
{
    // qDebug() << "Removed cookie: " << cookie;

    QList<QNetworkCookie> cookies = m_cookies.value(m_cookieFile);
    cookies.removeAll(cookie);
    m_cookies.insert(m_cookieFile, cookies);
}

}
