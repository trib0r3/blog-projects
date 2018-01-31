#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    void otworz_plik();                 // otwieranie pliku
    void zapisz_plik(QString = "");     // zapisywanie pliku

    void zamien();

    ~MainWindow();

private slots:
    void on_przycisk_clicked();
    void on_actionOtw_rz_triggered();

    void on_actionZapisz_triggered();
    void on_actionZapisz_jako_triggered();
    void on_actionZamknij_triggered();


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
