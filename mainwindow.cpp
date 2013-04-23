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
    connect(ui->guzikGraj, SIGNAL(clicked()), this, SLOT(graj()));
    connect(ui->rysownik, SIGNAL(graczPuscil()), this, SLOT(startSim()));

    this->setMouseTracking(true);
    ui->centralwidget->setMouseTracking(true);

    scena = new QGraphicsScene(0, 0, 800, 600);
    ui->rysownik->setScene(scena);
    ui->rysownik->setMouseTracking(true);
    scena->setBackgroundBrush((QBrush(QColor::fromRgb(0, 0, 0), Qt::SolidPattern)));

    sim = new Symulation();
    connect(sim, SIGNAL(powiadom(Kometa*,Wiadomosc)),
            this, SLOT(odbierzWiadomosc(Kometa*,Wiadomosc)), Qt::BlockingQueuedConnection);
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

    sim->usunPlanety();

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
        sim->dodajPlanete(kolo);
    }
}

void MainWindow::graj()
{
    gracz = new Kometa(Vector2(-100, -100), Vector2(0, 0));
    scena->addItem(gracz);
    ui->rysownik->przypiszGracz(gracz);
    ui->rysownik->ustawTrybGry(true);

    /*int x, y;
    Kometa *gracz;

    do {
        x = ( rand() % (int)(790) );
        y = ( rand() % (int)(590) );

        gracz = new Kometa(Vector2(x, y), Vector2(0, 0));

    } while (scena->collidingItems(gracz).count());

    qDebug() << "gracz na pozycji == " << gracz->zwrocSrodek().x << " :: " << gracz->zwrocSrodek().y;

    scena->addItem(gracz);

    sim->dodajGracza(gracz);
    sim->start();*/



}

void MainWindow::odbierzWiadomosc(Kometa *naCzym, Wiadomosc wiad)
{
    switch (wiad.typ) {
        case rusz : naCzym->ustawPozycje(Vector2(wiad.x, wiad.y));
    }
}

void MainWindow::startSim() {
    sim->dodajGracza(gracz);
    sim->start();
}
