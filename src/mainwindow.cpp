#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "webengineview.h"
#include "util.h"
#include "cookiemanager.h"
#include "colorscheme.h"

#include <QUrl>
#include <QIcon>
#include <QWebEngineCookieStore>
#include <QWebEngineProfile>
#include <QWebEngineScript>
#include <QWebEngineScriptCollection>
#include <QWebEngineSettings>
#include <QWebEnginePage>

#define CHATGPT_URL "https://chat.openai.com"
#define YIYAN_URL "https://yiyan.baidu.com"
#define TONGYI_URL "https://tongyi.aliyun.com/qianwen"
#define DOUBAO_URL "https://www.doubao.com"

MainWindow::MainWindow(Gpt::ColorScheme *scheme, QWidget *parent)
    : QMainWindow{parent}
    , ui(new Ui::MainWindow)
    , view(new Gpt::WebEngineView)
    , colorScheme(scheme)
{
    ui->setupUi(this);
    setCentralWidget(view);

    ui->actChatGPT->setIcon(QIcon(Gpt::Util::getRoundedPixmap(":/assets/ChatGPT.jpg")));
    ui->actDoubao->setIcon(QIcon(Gpt::Util::getRoundedPixmap(":/assets/doubao.png")));
    ui->actYiyan->setIcon(QIcon(Gpt::Util::getRoundedPixmap(":/assets/yiyan.png")));
    ui->actTongyi->setIcon(QIcon(Gpt::Util::getRoundedPixmap(":/assets/tongyi.png")));

    QWebEngineCookieStore *cookieStore = view->page()->profile()->cookieStore();
    cookieManager = new Gpt::CookieManager(cookieStore, this);
    cookieStore->loadAllCookies();
    on_actChatGPT_triggered();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete view;
    delete cookieManager;
}

void MainWindow::showWebView(QString url)
{
    cookieManager->setCookieFile(url);
    cookieManager->loadCookies();

    QString script = R"(
document.documentElement.style.overflow = 'hidden';
document.body.style.overflow = 'hidden';
)";
    QWebEngineScript userScript;
    userScript.setInjectionPoint(QWebEngineScript::DocumentReady);
    userScript.setSourceCode(script);

    view->page()->scripts().insert(userScript);
    view->load(QUrl(url));
}

void MainWindow::on_actChatGPT_triggered()
{
    // // Inject JavaScript to detect system color scheme and apply styles
    // QString script = R"(
    //     var prefersDarkScheme = window.matchMedia('(prefers-color-scheme: dark)').matches;
    //     if (prefersDarkScheme) {
    //         document.documentElement.style.colorScheme = 'dark';
    //         document.documentElement.className = 'dark';
    //     } else {
    //         document.documentElement.style.colorScheme = 'light';
    //         document.documentElement.className = 'light';
    //     }
    // )";

    QString dark = R"(
document.documentElement.style.colorScheme = 'dark';
document.documentElement.className = 'dark';
)";
    QString light = R"(
document.documentElement.style.colorScheme = 'light';
document.documentElement.className = 'light';
)";
    QWebEngineScript userScript;
    // userScript.setName("SetColorScheme");
    userScript.setInjectionPoint(QWebEngineScript::DocumentReady);
    // userScript.setRunsOnSubFrames(false);
    userScript.setWorldId(QWebEngineScript::ApplicationWorld);

    if (colorScheme->isDarkMode())
    {
        // view->page()->runJavaScript(dark);
        userScript.setSourceCode(dark);
    }
    else if (colorScheme->isLightMode())
    {
        // view->page()->runJavaScript(light);
        userScript.setSourceCode(light);
    }

    view->page()->scripts().insert(userScript);

    showWebView(CHATGPT_URL);
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

void MainWindow::syncBgColorStyle()
{
    QString dark = R"(
document.documentElement.style.background = '#212121';
document.documentElement.style.backgroundColor = '#212121';
document.documentElement.style.color = '#ffffff';
document.body.style.background = '#212121';
document.body.style.backgroundColor = '#212121';
document.body.style.color = '#ffffff';
)";
    QString light = R"(
document.documentElement.style.background = '#ffffff';
document.documentElement.style.backgroundColor = '#ffffff';
document.documentElement.style.color = '#000000';
document.body.style.background = '#ffffff';
document.body.style.backgroundColor = '#ffffff';
document.body.style.color = '#000000';
)";
    QWebEngineScript userScript;
    userScript.setInjectionPoint(QWebEngineScript::DocumentReady);

    if (colorScheme->isDarkMode())
        userScript.setSourceCode(dark);
    else if (colorScheme->isLightMode())
        userScript.setSourceCode(light);

    view->page()->scripts().insert(userScript);
}
