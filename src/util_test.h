#ifndef UTIL_TEST_H
#define UTIL_TEST_H

#include "util.h"

#include <QObject>
#include <QtTest/QTest>

namespace Gpt
{

class UtilTest : public QObject
{
    Q_OBJECT

private slots:
    // Test case for encryptData method
    void testEncryptData()
    {
        QByteArray originalData = "Sensitive information";
        QByteArray key = "Your Secret Key";

        QByteArray encryptedData = Util::encryptData(originalData, key);

        QVERIFY(!encryptedData.isEmpty());
    }

    // Test case for decryptData method
    void testDecryptData()
    {
        QByteArray originalData = "Sensitive information";
        QByteArray key = "Your Secret Key ";

        QByteArray encryptedData = Util::encryptData(originalData, key);
        QByteArray decryptedData = Util::decryptData(encryptedData, key);

        QCOMPARE(decryptedData, originalData);
    }
};

}

#endif // UTIL_TEST_H
