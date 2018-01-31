#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

QByteArray array;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    port = new QSerialPort(this);

    searchDevice();
    update();

    connect(port,SIGNAL(readyRead()),this,SLOT(readData()));
}

MainWindow::~MainWindow()
{
    if(port->isOpen())
        port->close();

    delete port;
    delete ui;
}


// wyszukiwanie pojedynczego urządzenia
void MainWindow::searchDevice()
{
    QList <QSerialPortInfo> list;
    list = QSerialPortInfo::availablePorts();

    if(list.size() == 1) {
        port->setPort(list.at(0));
        port->open(QIODevice::ReadWrite);


    }
    else {
        int  answer = QMessageBox::warning(this,"Błąd!","Nie znaleziono pojedynczego portu, spróbować ponownie?",
                                           QMessageBox::Yes,QMessageBox::No);
        switch(answer)
        {
        case QMessageBox::Yes:
            return searchDevice();
            break;

        case QMessageBox::No:
            qApp->deleteLater();
            break;
        }
    }
}


// prosimy o natychmiastowe podesłanie temperatury
void MainWindow::on_zmierz_clicked()
{
   if(port->isOpen()) {
       char c = '!';
       port->write(&c);
       port->waitForBytesWritten(-1);
   }
   else
       QMessageBox::information(this,"Błąd","Odłączono urządzenie!");
}


// aktualizacja widgetów, po odebraniu danych
void MainWindow::update(int value)
{
    // ustawiamy wartość temperatury
    ui->temperatura->display(value);
    // zmieniamy date ostatniej aktualizacji
    ui->lastUpdate->setDateTime(QDateTime(QDate::currentDate(),QTime::currentTime()));
}


// wczytywanie danych
void MainWindow::readData()
{
    array = port->readAll();
    while(port->waitForReadyRead(100))
        array += port->readAll();

    QString a(array);

    if(a.at(0) == '@' && a.at(a.size()-1) == '$') {
        a.remove('$');
        a.remove('@');
        update(a.toInt());
        array.clear();
    }
}
