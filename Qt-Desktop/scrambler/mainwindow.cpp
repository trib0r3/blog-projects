#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QWebElement>
#include <QWebFrame>
#include <QMessageBox>



// ---------------------------------------
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&webView,SIGNAL(loadFinished(bool)),this,SLOT(zaladowano()) );

    QWebSettings * globalSettings = QWebSettings::globalSettings();
            globalSettings->setAttribute(QWebSettings::AutoLoadImages, false);
            globalSettings->setAttribute(QWebSettings::JavaEnabled, false);
            globalSettings->setAttribute(QWebSettings::PluginsEnabled, false);
            globalSettings->setAttribute(QWebSettings::JavascriptCanOpenWindows, false);
            globalSettings->setAttribute(QWebSettings::JavascriptCanCloseWindows, false);
            globalSettings->setAttribute(QWebSettings::JavascriptCanAccessClipboard, false);
            globalSettings->setAttribute(QWebSettings::DeveloperExtrasEnabled, false);
            globalSettings->setAttribute(QWebSettings::SpatialNavigationEnabled, false);
            globalSettings->setAttribute(QWebSettings::PrintElementBackgrounds, false);

}

MainWindow::~MainWindow()
{
    webView.close();
    delete ui;
}


void MainWindow::on_losuj_clicked()
{
    // zablokujmy możlwiość wciśnięcia przycisku "Losuj" dopóki nie wczytamy strony
    ui->losuj->setEnabled(false);

    // rozpoczynamy wczytywanie strony
    webView.load(QUrl("http://www.cubetimer.com/"));
}


void MainWindow::zaladowano()
{
    // szukamy wszystkich tagów <b>
    QWebElement strona = webView.page()->mainFrame()->documentElement().findFirst("div[id=scramble]");

    QString scr =  strona.toPlainText();
    // skracamy go aby był bez napisu "Scramble: "
    scr.remove(0,9);

    // z racji, że strona w tych tagach ma także numer scramble'a to pobieramy drugi
    ui->scramble->setText(scr);

    // aktywujemy możlwiość losowania
    ui->losuj->setEnabled(true);
}
