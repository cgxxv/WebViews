#include "mainwindow.h"
#include "util.h"

#include <QApplication>
#include <QIcon>
#include <QPixmap>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    const QPixmap rounded = Gpt::Util::get_rounded_pixmap(":/assets/ChatGPT.svg");
    a.setWindowIcon(QIcon(rounded));

    MainWindow w;
    w.resize(1024,768);
    w.show();

    return a.exec();
}
