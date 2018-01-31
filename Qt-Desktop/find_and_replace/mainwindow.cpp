#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>


// zmiennie globalne

QString tekst;             // tekst znajdujący się w polu tekstowym

QString szukany_tekst;     // tekst, który zamienimy na inny
QString zamiennik;         // tekst na jaki zostanie zamieniona szukana fraza

QString poprzedniaSciezka; // poprzednia ścieżka do pliku



// ---------------------------------------
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

// funkcje pomocnicze
void MainWindow::otworz_plik()
{
    // QFileDialog::getOpenFileName([rodzic (parent)],[tytuł nagłówka],
    // [ścieżka od której rozpoczyna się wyszukiwanie pliku], [rozszerzenia wyszukiwanych plików])
    QString fileName = QFileDialog::getOpenFileName(this,tr("Otwórz..."), "/home/", tr("Pliki txt (*.txt)"));
    if(fileName.isEmpty())
        return;

    QFile plik(fileName);

    // możemy tylko czytać dane, oraz wczytujemy je jako tekst:
    if(!plik.open(QIODevice::ReadOnly | QIODevice::Text))
        return;             // jeżeli nie udało się otworzyć pliku: przerwij wczytywanie pliku

    // czyścimy wcześniej zapełnioną zmienną tekstową
    tekst.clear();

    QTextStream stream(&plik);

    // czytamy wszystkie dane
    tekst = stream.readAll();

    // umieszczamy je wewnątrz text boxa
    ui->poleTekstowe->setText(tekst);

    poprzedniaSciezka = fileName;

    plik.close();
}


void MainWindow::zapisz_plik(QString fileName)
{
    tekst = ui->poleTekstowe->toPlainText();

    if(fileName.isEmpty())
        fileName = QFileDialog::getSaveFileName
                (this,tr("Zapisz plik jako..."),tr("/home/"),tr("Pliki tekstowe (*.txt)"));

    if(fileName.isEmpty())
        return;

    QFile plik(fileName);
    plik.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text);

    QTextStream stream(&plik);
    stream << tekst;

    poprzedniaSciezka = fileName;

    plik.close();
}


void MainWindow::zamien()
{
    tekst = ui->poleTekstowe->toPlainText();
    szukany_tekst = ui->wyszukaj->text();
    zamiennik = ui->zamien_na->text();

    if(tekst.isEmpty() || szukany_tekst.isEmpty() || zamiennik.isEmpty())
        return;

    int poz = 0;            // pozycja od której ma być szukany tekst
    int znaleziono = 0;     // ile znaleziono takich słów
    while((poz = tekst.indexOf(szukany_tekst,poz)) != -1)
    {
        tekst.replace(poz,zamiennik.size(),zamiennik);
        poz += zamiennik.size();
        znaleziono ++;
    }
    ui->poleTekstowe->setText(tekst);
    QMessageBox::information(this,tr("Raport"),"Znaleziono "+QString::number(znaleziono)+" wyrazów.");
}


// sloty
void MainWindow::on_actionOtw_rz_triggered()
{
    otworz_plik();
}


void MainWindow::on_actionZapisz_triggered()
{
    zapisz_plik(poprzedniaSciezka);
}


void MainWindow::on_actionZapisz_jako_triggered()
{
    zapisz_plik();
}


void MainWindow::on_actionZamknij_triggered()
{
    qApp->exit();
}


void MainWindow::on_przycisk_clicked()
{
    zamien();
}
