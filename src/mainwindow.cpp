#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "webengineview.h"
#include "util.h"
#include "cookiemanager.h"

#include <QUrl>
#include <QIcon>
#include <QWebEngineCookieStore>
#include <QWebEngineProfile>
#include <QDir>

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

    ui->actChatGPT->setIcon(QIcon(Gpt::Util::getRoundedPixmap(":/assets/ChatGPT.jpg")));
    ui->actDoubao->setIcon(QIcon(Gpt::Util::getRoundedPixmap(":/assets/doubao.png")));
    ui->actYiyan->setIcon(QIcon(Gpt::Util::getRoundedPixmap(":/assets/yiyan.png")));
    ui->actTongyi->setIcon(QIcon(Gpt::Util::getRoundedPixmap(":/assets/tongyi.png")));

    QWebEngineCookieStore *cookieStore = view->page()->profile()->cookieStore();
    cookieManager = new Gpt::CookieManager(cookieStore, this);
    cookieStore->loadAllCookies();
    showWebView(CHATGPT_URL);
    setCentralWidget(view);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete view;
    delete cookieManager;
}

void MainWindow::showWebView(QString url)
{
    QString hashedUrl = QString::fromLatin1(url.toUtf8().toHex());
    QString cookieFilePath = QDir::currentPath()+"/"+hashedUrl+".cookies.dat";
    qInfo() << "url: " << url << ", Cookie filepath: " << cookieFilePath;
    cookieManager->setCookieFilePath(cookieFilePath);
    cookieManager->loadCookies();

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
    showWebView(CHATGPT_URL);
    view->page()->runJavaScript(dark);
}


void MainWindow::on_actYiyan_triggered()
{
    showWebView(YIYAN_URL);
}


void MainWindow::on_actTongyi_triggered()
{
    showWebView(TONGYI_URL);
}


void MainWindow::on_actDoubao_triggered()
{
    showWebView(DOUBAO_URL);
}
