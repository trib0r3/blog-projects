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
    void on_port_currentIndexChanged(int index);
    void refresh();

    void on_commandLine_returnPressed();

    void on_enterButton_clicked();

private:
    Ui::MainWindow *ui;

    void searchDevices();
    void addTextToConsole(QString text, bool sender=false);

    void send(QString msg);
    void receive();
};

#endif // MAINWINDOW_H
