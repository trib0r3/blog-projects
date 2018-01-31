#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "settings.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void onFontChanged(QString);
    void onFontSizeChanged(int);

    void onBoldEnabled(bool);
    void onItalicEnabled(bool);
    void onUnderlineEnabled(bool);

    void onFontColorChanged(int,int,int);

private:
    Ui::MainWindow *ui;
    Settings *settings;

    void updateText();
};

#endif // MAINWINDOW_H
