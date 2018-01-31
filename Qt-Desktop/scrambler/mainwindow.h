#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebView>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QWebView webView;

    ~MainWindow();

private slots:
    void zaladowano();

    void on_losuj_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
