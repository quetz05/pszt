#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include "planeta.h"
#include <QGraphicsLineItem>
#include <time.h>
#include "kometascene.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ilePlanet = minWaga = maksWaga = 1;

    connect(ui->liczbaPlanet, SIGNAL(sliderMoved(int)), this, SLOT(ustawLiczbePlanet(int)));
    connect(ui->minWaga, SIGNAL(sliderMoved(int)), this, SLOT(ustawMinWage(int)));
    connect(ui->maksWaga, SIGNAL(sliderMoved(int)), this, SLOT(ustawMaksWage(int)));
    connect(ui->guzikGeneruj, SIGNAL(clicked()), this, SLOT(generujPlansze()));

    scena = new KometaScene(0, 0, 800, 600);
    ui->rysownik->setScene(scena);
    ui->rysownik->setMouseTracking(true);
    scena->setBackgroundBrush((QBrush(QColor::fromRgb(0, 0, 0), Qt::SolidPattern)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ustawLiczbePlanet(int wartosc) {
    ilePlanet = wartosc;
    ui->labelPlanety->setText(QString::number(wartosc));
}

void MainWindow::ustawMinWage(int wartosc) {
    minWaga = wartosc;
    ui->labelMinWaga->setText(QString::number(wartosc).append(" x 10 <sup>24</sup> kg"));
}

void MainWindow::ustawMaksWage(int wartosc) {
    maksWaga = wartosc;
    ui->labelMaksWaga->setText(QString::number(wartosc).append(" x 10 <sup>24</sup> kg"));
}

void MainWindow::generujPlansze()
{
    if (minWaga > maksWaga) {
        QMessageBox wiadomosc;
        wiadomosc.setWindowTitle("Błąd!");
        wiadomosc.setText("Waga minimalna jest większa od maksymalnej!");
        wiadomosc.addButton(QMessageBox::Ok);
        wiadomosc.setIcon(QMessageBox::Warning);
        wiadomosc.exec();
        return;
    }

    scena->clear();

    scena->addLine(-1, -1, 801, -1, QPen(QColor::fromRgb(255, 255, 255)));
    scena->addLine(-1, -1, -1, 601, QPen(QColor::fromRgb(255, 255, 255)));
    scena->addLine(801, -1, 801, 601, QPen(QColor::fromRgb(255, 255, 255)));
    scena->addLine(-1, 601, 801, 601, QPen(QColor::fromRgb(255, 255, 255)));

    Planeta *kolo = NULL;
    qreal prom;
    qreal masa;
    qreal x, y;
    srand(time(NULL));

    for (int i = 0; i < ilePlanet; ++i) {

        do {
            masa = ( rand() % ((maksWaga + 1) - minWaga) ) + minWaga;
            prom = 5 + 0.5 * masa;
            x = ( rand() % (int)(800 - 2*prom) );
            y = ( rand() % (int)(600 - 2*prom) );

            qDebug() << "dodaje :: " << masa << " :: " << prom << " :: " << x << " :: " << y;

            kolo = new Planeta(Vector2(x, y), masa);

        } while (scena->collidingItems(kolo).count());

        scena->addItem(kolo);
    }
}
