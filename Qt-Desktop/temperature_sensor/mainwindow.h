#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>

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
    void on_zmierz_clicked();
    void readData();

private:
    Ui::MainWindow *ui;

    void searchDevice();
    void update(int v=0);

    QSerialPort *port;
};

#endif // MAINWINDOW_H
