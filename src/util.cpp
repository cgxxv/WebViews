#include "util.h"

#include <QPixmap>
#include <QPainter>
#include <QPainterPath>
#include <QString>

namespace Gpt {

QPixmap Util::getRoundedPixmap(QString str)
{
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

}
