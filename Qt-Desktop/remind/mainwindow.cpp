#include "mainwindow.h"
#include "ui_mainwindow.h"


bool isTime = false;                // flaga do sprawdzania czy przy odliczaniu uwzgędniamy czas (godzinę), czy odliczamy minuty
QString message;

QTime time;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->label->setText(tr("(MM:SS)"));
    timer = new QTimer(this);
    timer->setSingleShot(true);

    connect(timer,SIGNAL(timeout()),this,SLOT(showMessage()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_isTime_clicked(bool checked)
{
    isTime = checked;

    if(!isTime) {
        ui->label->setText(tr("(MM:SS)"));
    }
    else {
        ui->label->setText(tr("Godzina eventu (HH:MM)"));
        ui->timeToMessage->setTime(QTime::currentTime());
    }
}

void MainWindow::on_start_clicked()
{
    if(ui->message->toPlainText().isEmpty()) return;

    ui->start->setEnabled(false);
    ui->stop->setEnabled(true);

    message = ui->message->toPlainText();

    ui->message->setEnabled(false);

    // odliczanie czasu
    time = ui->timeToMessage->time();

    int timeout=0;
    if(isTime)
    {
        if(time > QTime::currentTime())
            timeout = (time.hour()*3600+time.minute()*60+time.second()) -
                (QTime::currentTime().hour()*3600+QTime::currentTime().minute()*60+QTime::currentTime().second());
    }
    else
        timeout = time.hour()*60 + time.minute();

    ui->statusBar->showMessage(QString::number(timeout*1000));
    timer->start(timeout*1000);
}

void MainWindow::on_stop_clicked()
{
    ui->start->setEnabled(true);
    ui->message->setEnabled(true);

    timer->stop();
}


void MainWindow::showMessage()
{
    on_stop_clicked();

    QMessageBox::information(this,"Alarm!",message);
}
