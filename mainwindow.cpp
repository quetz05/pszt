#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include "planeta.h"
#include <QGraphicsLineItem>
#include <time.h>
#include "kometascene.h"
#include "QPushButton"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ilePlanet = minWaga = maksWaga = 1;
    counter = 0;
    pierwsza = true;

    for (int i = 0; i < NUM_THREADS; ++i) {
        gracz[i] = NULL;
        sim[i] = NULL;
    }

    qRegisterMetaType<Wiadomosc>("Wiadomosc");

    connect(ui->liczbaPlanet, SIGNAL(sliderMoved(int)), this, SLOT(ustawLiczbePlanet(int)));
    connect(ui->minWaga, SIGNAL(sliderMoved(int)), this, SLOT(ustawMinWage(int)));
    connect(ui->maksWaga, SIGNAL(sliderMoved(int)), this, SLOT(ustawMaksWage(int)));
    connect(ui->guzikGeneruj, SIGNAL(clicked()), this, SLOT(generujPlansze()));
    connect(ui->guzikGraj, SIGNAL(clicked()), this, SLOT(graj()));
    connect(ui->rysownik, SIGNAL(graczPuscil()), this, SLOT(startSim()));
    connect(ui->guzikSymuluj, SIGNAL(clicked()), this, SLOT(symuluj()));
    connect(ui->guzikNastepna, SIGNAL(clicked()), this, SLOT(nastepna()));

    this->setMouseTracking(true);
    ui->centralwidget->setMouseTracking(true);

    ui->guzikGraj->setEnabled(false);
    ui->guzikSymuluj->setEnabled(false);
    ui->guzikNastepna->setEnabled(false);
    ui->guzikTabela->setEnabled(false);

    ui->czasPole->setText("30");

    scena = new QGraphicsScene(0, 0, 800, 600);
    ui->rysownik->setScene(scena);
    ui->rysownik->setMouseTracking(true);
    scena->setBackgroundBrush((QBrush(QColor::fromRgb(0, 0, 0), Qt::SolidPattern)));

    sim[0] = new Symulation(0);
    connect(sim[0], SIGNAL(powiadom(Kometa*,Wiadomosc)),
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

    ui->guzikGraj->setEnabled(true);
    ui->guzikSymuluj->setEnabled(true);

    scena->clear();
    scena->update(0, 0, 800, 600);

    scena->addLine(-1, -1, 801, -1, QPen(QColor::fromRgb(255, 255, 255)));
    scena->addLine(-1, -1, -1, 601, QPen(QColor::fromRgb(255, 255, 255)));
    scena->addLine(801, -1, 801, 601, QPen(QColor::fromRgb(255, 255, 255)));
    scena->addLine(-1, 601, 801, 601, QPen(QColor::fromRgb(255, 255, 255)));

    Planeta *kolo = NULL;
    qreal prom;
    qreal masa;
    qreal x, y;
    srand(time(NULL));

    sim[0]->usunPlanety();
    planety.clear();
    for (int i = 0; i < ilePlanet; ++i) {

        do {
            masa = ( rand() % ((maksWaga + 1) - minWaga) ) + minWaga;
            prom = 5 + 0.5 * masa;
            x = ( rand() % (int)(800 - 2*prom) );
            y = ( rand() % (int)(600 - 2*prom) );

            kolo = new Planeta(Vector2(x, y), masa);

        } while (scena->collidingItems(kolo).count());

        scena->addItem(kolo);
        sim[0]->dodajPlanete(kolo);
        planety.push_back(kolo);
    }
}

void MainWindow::graj()
{
    ui->guzikSymuluj->setEnabled(false);

    if (gracz[0]) {
        scena->removeItem(gracz[0]);
        delete gracz[0];
    }

    gracz[0] = new Kometa(Vector2(-100, -100), Vector2(0, 0));
    scena->addItem(gracz[0]);
    ui->rysownik->przypiszGracz(gracz[0]);
    ui->rysownik->ustawTrybGry(true);
}

void MainWindow::symuluj()
{
    pop = new Populacja(&planety);
    connect(pop, SIGNAL(gotowe()), this, SLOT(narysuj()));
    pop->dawaj();

    ui->guzikNastepna->setEnabled(true);
}

void MainWindow::nastepna()
{
    pop->tworzNowaPopulacje();
}

void MainWindow::narysuj()
{

    QList<QGraphicsItem*> lista = scena->items();

    for (int i = 0; i < lista.size(); ++i) {
        Kometa *temp = dynamic_cast<Kometa*>(lista[i]);
        if (temp)
            scena->removeItem(temp);
    }

    int ile = pop->osobniki.size();

    for (int i = 0; i < ile; ++i) {
        pop->osobniki[i]->narysujSciezke();
        scena->addItem(pop->osobniki[i]);
    }

    scena->update(0, 0, 800, 600);

}

void MainWindow::odbierzWiadomosc(Kometa *naCzym, Wiadomosc wiad)
{
    switch (wiad.typ) {
        case rusz : naCzym->ustawPozycje(Vector2(wiad.x, wiad.y)); break;
                    break;
        case zakonczyl : ++counter;
                    break;
    }

    if (counter == NUM_THREADS) {
        for (int i = 0; i < NUM_THREADS; ++i) {
            gracz[i]->narysujSciezke();

        }
        scena->update(0, 0, 800, 600);
        scena->update(0, 0, 800, 600);
    }

}

void MainWindow::startSim() {
    sim[0]->dodajGracza(gracz[0]);
    sim[0]->start();
}
