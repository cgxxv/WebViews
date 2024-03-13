#include "util.h"

#include <QByteArray>
#include <QDebug>
#include <QPainter>
#include <QPainterPath>
#include <QPixmap>
#include <QString>

#include <openssl/err.h>
#include <openssl/evp.h>

namespace Gpt {

QPixmap Util::getRoundedPixmap(QString str) {
    const QPixmap orig = QPixmap(str);

    // getting size if the original picture is not square
    int size = qMax(orig.width(), orig.height());

    // creating a new transparent pixmap with equal sides
    QPixmap rounded = QPixmap(size, size);
    rounded.fill(Qt::transparent);

    // creating circle clip area
    QPainterPath path;
    path.addEllipse(rounded.rect());

    QPainter painter(&rounded);
    painter.setClipPath(path);

    // filling rounded area if needed
    painter.fillRect(rounded.rect(), Qt::black);

    // getting offsets if the original picture is not square
    int x = qAbs(orig.width() - size) / 2;
    int y = qAbs(orig.height() - size) / 2;
    painter.drawPixmap(x, y, orig.width(), orig.height(), orig);

    return rounded;
}

/**
 * @brief Encrypts the given data using AES encryption with CBC mode.
 *
 * @param data The data to be encrypted.
 * @param key The encryption key.
 * @param iv The initialization vector (IV).
 * @return QByteArray The encrypted data.
 * @throws std::runtime_error if encryption fails.
 */
QByteArray Util::encryptData(const QByteArray &data, const QByteArray &key) {
    // Initialization vector (IV)
    QByteArray iv(16, 0); // 16 bytes IV for AES-256-CBC

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        // throw std::runtime_error("Failed to create encryption context");
        handleOpenSSLErrors();
        return nullptr;
    }

    QByteArray ciphertext;
    int len;
    int ciphertext_len;

    if (1 != EVP_EncryptInit_ex(
            ctx, EVP_aes_256_cbc(), nullptr,
            reinterpret_cast<const unsigned char *>(key.constData()),
            reinterpret_cast<const unsigned char *>(iv.constData()))) {
        EVP_CIPHER_CTX_free(ctx);
        // throw std::runtime_error("Failed to initialize encryption");
        handleOpenSSLErrors();
        return nullptr;
    }

    // Resize ciphertext to accommodate encrypted data
    ciphertext.resize(data.size() + EVP_CIPHER_CTX_block_size(ctx));

    // Perform encryption
    if (1 != EVP_EncryptUpdate(
            ctx, reinterpret_cast<unsigned char *>(ciphertext.data()), &len,
            reinterpret_cast<const unsigned char *>(data.constData()),
            data.size())) {
        EVP_CIPHER_CTX_free(ctx);
        // throw std::runtime_error("Encryption error (update)");
        handleOpenSSLErrors();
        return nullptr;
    }
    ciphertext_len = len;

    // Finalize encryption
    if (1 != EVP_EncryptFinal_ex(ctx,
                                 reinterpret_cast<unsigned char *>(
                                     ciphertext.data() + ciphertext_len),
                                 &len)) {
        EVP_CIPHER_CTX_free(ctx);
        // throw std::runtime_error("Encryption error (final)");
        handleOpenSSLErrors();
        return nullptr;
    }
    ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);
    ciphertext.resize(ciphertext_len);
    return ciphertext;
}

/**
 * @brief Decrypts the given ciphertext using AES decryption with CBC mode.
 *
 * @param ciphertext The ciphertext to be decrypted.
 * @param key The encryption key.
 * @param iv The initialization vector (IV).
 * @return QByteArray The decrypted data.
 * @throws std::runtime_error if decryption fails.
 */
QByteArray Util::decryptData(const QByteArray &ciphertext,
                             const QByteArray &key) {
    // Initialization vector (IV)
    QByteArray iv(16, 0); // 16 bytes IV for AES-256-CBC

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        // throw std::runtime_error("Failed to create decryption context");
        handleOpenSSLErrors();
        return nullptr;
    }

    QByteArray plaintext;
    int len;
    int plaintext_len;

    if (1 != EVP_DecryptInit_ex(
            ctx, EVP_aes_256_cbc(), nullptr,
            reinterpret_cast<const unsigned char *>(key.constData()),
            reinterpret_cast<const unsigned char *>(iv.constData()))) {
        EVP_CIPHER_CTX_free(ctx);
        // throw std::runtime_error("Failed to initialize decryption");
        handleOpenSSLErrors();
        return nullptr;
    }

    // Resize plaintext to accommodate decrypted data
    plaintext.resize(ciphertext.size());

    // Perform decryption
    if (1 != EVP_DecryptUpdate(
            ctx, reinterpret_cast<unsigned char *>(plaintext.data()), &len,
            reinterpret_cast<const unsigned char *>(ciphertext.constData()),
            ciphertext.size())) {
        EVP_CIPHER_CTX_free(ctx);
        // throw std::runtime_error("Decryption error (update)");
        handleOpenSSLErrors();
        return nullptr;
    }
    plaintext_len = len;

    // Finalize decryption
    if (1 != EVP_DecryptFinal_ex(ctx,
                                 reinterpret_cast<unsigned char *>(
                                     plaintext.data() + plaintext_len),
                                 &len)) {
        EVP_CIPHER_CTX_free(ctx);
        // throw std::runtime_error("Decryption error (final)");
        handleOpenSSLErrors();
        return nullptr;
    }
    plaintext_len += len;

    EVP_CIPHER_CTX_free(ctx);
    plaintext.resize(plaintext_len);
    return plaintext;
}

void Util::handleOpenSSLErrors() {
    char errorBuffer[256];
    ERR_error_string(ERR_get_error(), errorBuffer);
    qCritical() << "OpenSSL Error:" << errorBuffer;
}

} // namespace Gpt
