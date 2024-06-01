#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "webengineview.h"
#include "util.h"
#include "colorscheme.h"
#include "profilemanager.h"

#include <QUrl>
#include <QIcon>
#include <QWebEngineCookieStore>
#include <QWebEngineScript>
#include <QWebEngineScriptCollection>
#include <QWebEngineSettings>

#define CHATGPT_URL "https://chat.openai.com"
#define YIYAN_URL "https://yiyan.baidu.com"
#define TONGYI_URL "https://tongyi.aliyun.com/qianwen"
#define DOUBAO_URL "https://www.doubao.com"

MainWindow::MainWindow(Gpt::ColorScheme *scheme, Gpt::WebEngineView *view, QWidget *parent)
    : QMainWindow{parent}
    , ui(new Ui::MainWindow)
    , view(view)
    , colorScheme(scheme)
    , profileManager(new Gpt::ProfileManager)
{
    ui->setupUi(this);
    setCentralWidget(view);

    ui->actChatGPT->setIcon(QIcon(Gpt::Util::getRoundedPixmap(":/assets/ChatGPT.jpg")));
    ui->actDoubao->setIcon(QIcon(Gpt::Util::getRoundedPixmap(":/assets/doubao.png")));
    ui->actYiyan->setIcon(QIcon(Gpt::Util::getRoundedPixmap(":/assets/yiyan.png")));
    ui->actTongyi->setIcon(QIcon(Gpt::Util::getRoundedPixmap(":/assets/tongyi.png")));

    on_actChatGPT_triggered();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete view;
    delete colorScheme;
    delete profileManager;
}

void MainWindow::showWebView(QString url)
{
    auto page = profileManager->getProfile(url);
    view->setPage(page);
    page->setDevToolsPage(view->page());

    QString script = R"(
document.documentElement.style.overflow = 'hidden';
document.body.style.overflow = 'hidden';
)";
    if (colorScheme->isDarkMode()) {
        qDebug() << "in dark mode";
        script.append(colorScheme->getDarkModeScript());
    } else {
        qDebug() << "in light mode";
        script.append(colorScheme->getLightModeScript());
    }

    QWebEngineScript userScript;
    userScript.setInjectionPoint(QWebEngineScript::DocumentReady);
    userScript.setSourceCode(script);

    view->page()->scripts().insert(userScript);
    view->load(QUrl(url));
}

void MainWindow::on_actChatGPT_triggered()
{
    colorScheme->setCurrentGpt(GPT_CHATGPT);
    showWebView(CHATGPT_URL);
}

void MainWindow::on_actYiyan_triggered()
{
    colorScheme->setCurrentGpt(GPT_YIYAN);
    showWebView(YIYAN_URL);
}

void MainWindow::on_actTongyi_triggered()
{
    colorScheme->setCurrentGpt(GPT_TONGYI);
    showWebView(TONGYI_URL);
}


void MainWindow::on_actDoubao_triggered()
{
    colorScheme->setCurrentGpt(GPT_DOUBAO);
    showWebView(DOUBAO_URL);
}
