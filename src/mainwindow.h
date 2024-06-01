#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWebEngineWidgets/QWebEngineView>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace Gpt {
class WebEngineView;
class ColorScheme;
class ProfileManager;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(Gpt::ColorScheme *scheme, Gpt::WebEngineView *view, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actChatGPT_triggered();
    void on_actYiyan_triggered();
    void on_actTongyi_triggered();
    void on_actDoubao_triggered();

private:
    // void syncBgColorStyle();
    void showWebView(QString url);

private:
    Ui::MainWindow *ui;
    Gpt::WebEngineView *view;
    Gpt::ColorScheme *colorScheme;
    Gpt::ProfileManager *profileManager;
};

#endif // MAINWINDOW_H
