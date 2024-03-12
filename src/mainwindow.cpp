#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "webengineview.h"
#include "util.h"

#include <QUrl>
#include <QIcon>

#define CHATGPT_URL "https://chat.openai.com"
#define YIYAN_URL "https://yiyan.baidu.com"
#define TONGYI_URL "https://tongyi.aliyun.com/qianwen"
#define DOUBAO_URL "https://www.doubao.com"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
    , ui(new Ui::MainWindow)
    , view(new Gpt::WebEngineView)
{
    ui->setupUi(this);

    ui->actChatGPT->setIcon(QIcon(Gpt::Util::get_rounded_pixmap(":/assets/ChatGPT.svg")));
    ui->actDoubao->setIcon(QIcon(Gpt::Util::get_rounded_pixmap(":/assets/doubao.png")));
    ui->actYiyan->setIcon(QIcon(Gpt::Util::get_rounded_pixmap(":/assets/yiyan.png")));
    ui->actTongyi->setIcon(QIcon(Gpt::Util::get_rounded_pixmap(":/assets/tongyi.png")));

    show_web_view(CHATGPT_URL);
    setCentralWidget(view);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete view;
}

void MainWindow::show_web_view(QString url)
{
    view->load(QUrl(url));
    QString script = R"(
document.documentElement.style.overflow = 'hidden';
document.documentElement.style.height = '100vh';
document.documentElement.style.margin = 0;
document.body.style.overflow = 'hidden';
document.body.style.height = '100vh';
document.body.style.margin = 0;
)";

    view->page()->runJavaScript(script);
}

void MainWindow::on_actChatGPT_triggered()
{
    QString dark = R"(
document.documentElement.style.colorScheme = 'dark';
document.documentElement.className = 'dark';
)";
    QString light = R"(
document.documentElement.style.colorScheme = 'light';
document.documentElement.className = 'light';
)";
    show_web_view(CHATGPT_URL);
    view->page()->runJavaScript(dark);
}


void MainWindow::on_actYiyan_triggered()
{
    show_web_view(YIYAN_URL);
}


void MainWindow::on_actTongyi_triggered()
{
    show_web_view(TONGYI_URL);
}


void MainWindow::on_actDoubao_triggered()
{
    show_web_view(DOUBAO_URL);
}
