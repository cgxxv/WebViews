#ifndef UTIL_H
#define UTIL_H

class QPixmap;
class QString;

namespace Gpt {

class Util
{
public:
    explicit Util() {};

    static QPixmap get_rounded_pixmap(QString str);
};

}

#endif // UTIL_H
