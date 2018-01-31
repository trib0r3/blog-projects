#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QTextEdit>

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();

    void setBasicSettins(QTextEdit *edit);

signals:
    void fontChanged(QString);                      // zmiana czcionki
    void fontSizeChanged(int);                      // zmiana rozmiaru czcionki

    void fontBoldSet(bool);                         // zmieniono pogrubienie tekstu
    void fontItalicSet(bool);                       // zmieniono kursywe tekstu
    void fontUnderlineSet(bool);                    // zmieniono podkreślenie tekstu

    void fontColorChanged(int,int,int);             // zmieniono kolor

private slots:
    void on_fontName_currentIndexChanged(const QString &arg1);
    void on_fontSize_valueChanged(int arg1);

    void on_fontBold_clicked();
    void on_fontItalic_clicked();
    void on_fontUnderline_clicked();

    void on_fontColorR_valueChanged(int arg1);
    void on_fontColorG_valueChanged(int arg1);
    void on_fontColorB_valueChanged(int arg1);

private:
    Ui::Settings *ui;
};

#endif // SETTINGS_H
