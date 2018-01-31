#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    settings = new Settings(this);
    settings->setBasicSettins(ui->content);

    settings->show();

    connect(settings,SIGNAL(fontChanged(QString)),this,SLOT(onFontChanged(QString)));
    connect(settings,SIGNAL(fontSizeChanged(int)),this,SLOT(onFontSizeChanged(int)));

    connect(settings,SIGNAL(fontBoldSet(bool)),this,SLOT(onBoldEnabled(bool)));
    connect(settings,SIGNAL(fontItalicSet(bool)),this,SLOT(onItalicEnabled(bool)));
    connect(settings,SIGNAL(fontUnderlineSet(bool)),this,SLOT(onUnderlineEnabled(bool)));

    connect(settings,SIGNAL(fontColorChanged(int,int,int)),this,SLOT(onFontColorChanged(int,int,int)));

    ui->content->setAutoFormatting(QTextEdit::AutoAll);
}


MainWindow::~MainWindow()
{
    delete settings;
    delete ui;
}


void MainWindow::updateText()
{
    QString str(ui->content->toPlainText());
    ui->content->setPlainText(str);
}


void MainWindow::onFontChanged(QString name)
{
    ui->content->setFontFamily(name);
    updateText();
}


void MainWindow::onFontSizeChanged(int size)
{
    ui->content->setFontPointSize(size);
    updateText();
}


void MainWindow::onBoldEnabled(bool enabled)
{
    if(enabled)
        ui->content->setFontWeight(75);
    else ui->content->setFontWeight(10);

    updateText();
}


void MainWindow::onItalicEnabled(bool e)
{
    ui->content->setFontItalic(e);
    updateText();
}


void MainWindow::onUnderlineEnabled(bool e)
{
    ui->content->setFontUnderline(e);
    updateText();
}


void MainWindow::onFontColorChanged(int r, int g, int b)
{
    ui->content->setTextColor(QColor(r,g,b));
    updateText();
}
