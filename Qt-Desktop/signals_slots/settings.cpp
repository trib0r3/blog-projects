#include "settings.h"
#include "ui_settings.h"

bool bold = false;
bool italic = false;
bool underline = false;

QColor color;

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_fontName_currentIndexChanged(const QString &arg1)
{
    emit fontChanged(arg1);
}



void Settings::on_fontSize_valueChanged(int arg1)
{
    // można dobrać się do tej wartości w ten sposób
    emit fontSizeChanged(ui->fontSize->value());
}


void Settings::on_fontBold_clicked()
{
    bold = !bold;
    emit fontBoldSet(bold);
}


void Settings::on_fontItalic_clicked()
{
    italic = !italic;
    emit fontItalicSet(italic);
}


void Settings::on_fontUnderline_clicked()
{
    underline = !underline;
    emit fontUnderlineSet(underline);
}


void Settings::on_fontColorR_valueChanged(int arg1)
{
    color.setRed(arg1);
    emit fontColorChanged(color.red(),color.green(),color.blue());
}


void Settings::on_fontColorG_valueChanged(int arg1)
{
    color.setGreen(arg1);
    emit fontColorChanged(color.red(),color.green(),color.blue());
}


void Settings::on_fontColorB_valueChanged(int arg1)
{
    color.setBlue(arg1);
    emit fontColorChanged(color.red(),color.green(),color.blue());
}


void Settings::setBasicSettins(QTextEdit *edit)
{
    ui->fontName->setFont(edit->currentFont());
    ui->fontSize->setValue((int)edit->font().pointSize());

    // pomijamy sprawdzenie czy jest bold, italic i underline bo nie jest

    ui->fontColorR->setValue(edit->textColor().red());
    ui->fontColorG->setValue(edit->textColor().green());
    ui->fontColorB->setValue(edit->textColor().blue());
}
