#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFileDialog>
#include<QMessageBox>
#include<QImage>
#include<QPixmap>

static const QVector<QRgb> colors = QVector<QRgb>()
        << qRgb(  0,   0,   0)
        << qRgb(255,   0,   0)
        << qRgb(  0, 255,   0)
        << qRgb(255, 255,   0)
        << qRgb(  0,   0, 255)
        << qRgb(255,   0, 255)
        << qRgb(  0, 255, 255)
        << qRgb(255, 255, 255);

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

void MainWindow::on_actionAdd_triggered()
{
    // Tworzy QStringList i używa go do przechowywania nazw plików, które użytkownik wybiera do przeliczenia
    //QStringList fileNames = QFileDialog::getOpenFileNames(this, "Wybierz pliki, które zaostanš poddane procesowi konwertacji");
    QStringList fileNames = QFileDialog::getOpenFileNames(this, "Otwórz", "", tr("Image Files (*.png *.jpg *.bmp *.jpeg *.tiff)"));
    // jeżeli nie zostały zaznaczone rzadne pliki...
    if (fileNames.isEmpty())
    {
        return;
    }
    // Jeli zostały wybrane pliki (lub plik) - dodaje je do listy nazw
    this->ui->imageList->addItems(fileNames);
}

void MainWindow::on_actionStart_triggered()
{
    // Jeżeli nie ma plików na licie - komunikat
    if (this->ui->imageList->count() == 0)
    {
        QMessageBox::warning(this, "Bład", "Proszę wybrać conajmniej jeden plik z obrazem.", QMessageBox::Ok, NULL);
        return;
    }
    // Zdeklarowane QString zapisuje w katalogu wyjciowy
    QString outputDir;
/*
    // Jeli dirCheckBox (katalog wyjciowy taki sam jak wejciowy) nie jest ustawiony, ustawia to co jest wpisane w outputDirTextBox->text()
    if (this->ui->dirCheckBox->checkState() == Qt::Unchecked)
    {
        if (this->ui->outputDirTextBox->text().isEmpty())
        {
            // Jeżeli outputDirTextBox jest pusty, zatrzymaj i pokaż komunikat
            QMessageBox::warning(this, "Błšd", "Nie został okrelony katalog plików wynikowych", QMessageBox::Ok, NULL);
            return;
        }
        else
        {
            // Jeli jest podany outputDirTextBox...
            outputDir = this->ui->outputDirTextBox->text();
        }
    }
    // Jeli dirCheckBox jest ustawiony, ustaw outputDir na NULL
    else
    {
        outputDir = QString::null;
    }
    // Zamyka okno zanim zanicze konwetrowanie
    this->setEnabled(false);


    // upewnia się, że okno zostanie natychmiast wyłšczone
    QApplication::processEvents();

    QMessageBox::information(NULL, "WOW", "Konwertowanie pliku zakończyło się powodzeniem", QMessageBox::NoIcon, NULL);
    // Jeli katalog / cieżka wyjciowy/a różni się od wejciowego
    if (outputDir != QString::null)
    {
        // Wykonuje iterację elementów Imagelist
        for (int row = 0; row < this->ui->imageList->count(); row++)
        {
            // Tworzy QListWidgetItem z jeden po drugim
            QListWidgetItem *item = this->ui->imageList->item(row);

            // Sprawdza czy plik istnieje
            if (!QFile(item->text()).exists())
            {
                // Jeli nie, ostrzega użytkownika, i przechodzi do następnej iteracji pętli "for"
                QMessageBox::warning(this, "Błšd", "Nie znaleziono pliku '" + item->text() + "'. Sprawd czy plik istnieje.");
                continue;
            }

            // Konwertuje pliki z ustawionymi parametrami
            if (Converter(NULL).Convert(item->text(), outputDir, QString(this->ui->outputFormatComboBox->currentText()), this->ui->qualitySpinBox->value(), this->ui->overwriteCheckBox->checkState() == Qt::Checked) && this->ui->deleteOriginalCheckBox->checkState() == Qt::Checked)
            {
                // jeli obraz został przekształcony pomylnie, a użytkownik wybrał deleteOriginalCheckBox, usuwany jest oryginalny plik
                QFile::remove(item->text());
            }
        }
    }
    // jeli katalog wyjciowy jest NULL (jest taki sam jak w katalogu wejciowego)
    else
    {
        // Wykonuje iterację elementów Imagelist
        for (int row = 0; row < this->ui->imageList->count(); row++)
        {
            // Tworzy QListWidgetItem z jeden po drugim
            QListWidgetItem *item = this->ui->imageList->item(row);

            // Sprawdza czy plik istnieje
            if (!QFile(item->text()).exists())
            {
                // Jeli nie, ostrzega użytkownika, i przechodzi do następnej iteracji pętli "for"
                QMessageBox::warning(this, "Błšd", "Nie znaleziono pliku '" + item->text() + "'. Sprawd czy plik istnieje.");
                continue;
            }

            // Konwertuje pliki z ustawionymi parametrami, i pomija parametr katalogu wyjciowego (ponieważ jest taki sam jak wejciowy.
            if (Converter(NULL).Convert(item->text(), QString(this->ui->outputFormatComboBox->currentText()), this->ui->qualitySpinBox->value(), this->ui->overwriteCheckBox->checkState() == Qt::Checked) && this->ui->deleteOriginalCheckBox->checkState() == Qt::Checked)
            {
                // jeli obraz został przekształcony pomylnie, a użytkownik wybrał deleteOriginalCheckBox, usuwany jest oryginalny plik
                QFile::remove(item->text());
            }
        }
    }
    // Włšczenie okna
    */
    this->setEnabled(true);
}

void MainWindow::on_imageList_itemClicked(QListWidgetItem *item)
{
    QPixmap pix(ui->imageList->currentItem()->text());
    if(ui->label->maximumHeight() < ui->label->maximumWidth())
    pix = pix.scaledToWidth(ui->label->maximumWidth());
    else pix = pix.scaledToHeight(ui->label->maximumHeight());
    ui->label->setPixmap(pix);

}
