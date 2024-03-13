#ifndef UTIL_H
#define UTIL_H

#include <QPixmap>
#include <QString>
#include <QByteArray>

namespace Gpt {

class Util
{
public:
    explicit Util() {};

    static QPixmap getRoundedPixmap(QString str);

    static QByteArray encryptData(const QByteArray &data, const QByteArray &key);
    static QByteArray decryptData(const QByteArray &encryptedData, const QByteArray &key);

private:
    static void handleOpenSSLErrors();
};

}

#endif // UTIL_H
