#ifndef PROFILEMANAGER_H
#define PROFILEMANAGER_H

#include "util.h"

#include <QString>
#include <QWebEnginePage>
#include <QWebEngineProfile>
#include <QWebEngineSettings>
#include <QMap>
#include <QCryptographicHash>

namespace Gpt
{

class ProfileManager
{
public:
    ProfileManager()  {}

    QWebEnginePage *getProfile(const QString &key)
    {
        auto page = m_profiles.value(key, nullptr);
        if (nullptr != page)
            return page;

        QByteArray md5sum = QCryptographicHash::hash(key.toUtf8(), QCryptographicHash::Md5);
        QString storagePath = Util::getStorageDir() + "/" + md5sum.toHex();

        auto profile = new QWebEngineProfile(md5sum.toHex());
        profile->setPersistentStoragePath(storagePath);

        page = new QWebEnginePage(profile);
        m_profiles.insert(key, page);

        return page;
    }

private:
    QMap<QString, QWebEnginePage*> m_profiles;
};

}

#endif // PROFILEMANAGER_H
