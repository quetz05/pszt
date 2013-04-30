#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include "planeta.h"
#include <QGraphicsLineItem>
#include <time.h>
#include "kometascene.h"
#include "QPushButton"
#include <QPlainTextEdit>
#include <QDialogButtonBox>
#include "zestawienie.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ileWykonal = 0;
    ilePlanet = ileObrotow = 1;
    minWaga = maksWaga = 10;
    counter = 0;
    pierwsza = true;
    pop = NULL;

    sim = NULL;
    gracz = NULL;

    QThreadPool::globalInstance()->setMaxThreadCount(30);
    qDebug() << "idealna ilosc watkow == " << QThread::idealThreadCount();
    qDebug() << "faktyczna ilosc watkow == " << QThreadPool::globalInstance()->maxThreadCount();

    qRegisterMetaType<Wiadomosc>("Wiadomosc");
    qRegisterMetaType<ProstaWiadomosc>("ProstaWiadomosc");

    connect(ui->liczbaPlanet, SIGNAL(sliderMoved(int)), this, SLOT(ustawLiczbePlanet(int)));
    connect(ui->minWaga, SIGNAL(sliderMoved(int)), this, SLOT(ustawMinWage(int)));
    connect(ui->maksWaga, SIGNAL(sliderMoved(int)), this, SLOT(ustawMaksWage(int)));
    connect(ui->liczbaObroto, SIGNAL(sliderMoved(int)), this, SLOT(ustawLiczbeObrotow(int)));
    connect(ui->guzikGeneruj, SIGNAL(clicked()), this, SLOT(generujPlansze()));
    connect(ui->guzikGraj, SIGNAL(clicked()), this, SLOT(graj()));
    connect(ui->rysownik, SIGNAL(graczPuscil()), this, SLOT(startSim()));
    connect(ui->guzikSymuluj, SIGNAL(clicked()), this, SLOT(symuluj()));
    connect(ui->guzikNastepna, SIGNAL(clicked()), this, SLOT(nastepna()));
    connect(ui->guzikTabela, SIGNAL(clicked()), this, SLOT(tabela()));

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

void MainWindow::ustawLiczbeObrotow(int wartosc)
{
    ileObrotow = wartosc;
    ui->labelObrotow->setText(QString::number(wartosc));
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

    ui->guzikSymuluj->setEnabled(true);
    ui->guzikNastepna->setEnabled(false);
    ui->guzikTabela->setEnabled(false);

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
        planety.push_back(kolo);
    }
}

void MainWindow::graj()
{

}

void MainWindow::symuluj()
{
    if (pop)
        delete pop;

    pop = new Populacja(&planety);
    connect(pop, SIGNAL(gotowe()), this, SLOT(narysuj()));
    connect(this, SIGNAL(next()), pop, SLOT(dzialaj()));
    connect(pop, SIGNAL(nadajWiadomosc(ProstaWiadomosc)), this, SLOT(odbierzProsta(ProstaWiadomosc)));

    pop->generujPierwsza();

    ui->guzikNastepna->setEnabled(true);
    ui->guzikTabela->setEnabled(true);
}

void MainWindow::nastepna()
{
    pop->dzialaj();

    ui->guzikNastepna->setEnabled(false);
    ui->guzikGeneruj->setEnabled(false);
    ui->guzikSymuluj->setEnabled(false);
    ui->guzikTabela->setEnabled(false);
}

void MainWindow::tabela()
{

    zest = new Zestawienie(this);
    zest->prepareData(pop);
    zest->show();
}

void MainWindow::narysujSymulacje()
{
    int id = QObject::sender()->objectName().toInt();
    qDebug() << "symulowanie " << id << " komety z wektorka";

    zest->close();

    QList<QGraphicsItem*> lista = scena->items();

    for (int i = 0; i < lista.size(); ++i) {
        Kometa *temp = dynamic_cast<Kometa*>(lista[i]);
        //if (temp)
          //  scena->removeItem(temp);
    }

    gracz = new Kometa(pop->osobniki[id]->zwrocPozycjePocz(), pop->osobniki[id]->zwrocKierunekPocz());
    gracz->ustawInteraktywne(true);
    gracz->narysujSciezke();
    gracz->ustawKolor(pop->osobniki[id]->zwrocKolor());

    qDebug() << gracz->zwrocPozycjePocz().x << " / " << gracz->zwrocPozycjePocz().y
             << " :: " << gracz->zwrocKierunekPocz().x << " / " << gracz->zwrocKierunekPocz().y;

    /*if (sim)
        delete sim;

    sim = new Symulation(0);
    sim->ustawInteraktywne(true);
    sim->dodajGracza(gracz);

    for (int i = 0; i < ilePlanet; ++i)
        sim->dodajPlanete(planety[i]);

    scena->addItem(gracz);

    connect(sim, SIGNAL(powiadom(Kometa*,Wiadomosc)), this, SLOT(odbierzWiadomosc(Kometa*,Wiadomosc)));*/

    Replay *rp = new Replay(gracz, pop->osobniki[id]->zwrocSciezke());
    connect(rp, SIGNAL(nadajWiadomosc(Kometa*,Wiadomosc)), this, SLOT(odbierzWiadomosc(Kometa*,Wiadomosc)));

    scena->addItem(gracz);

    QThreadPool::globalInstance()->start(rp);
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
        scena->update(0, 0, 800, 600);
                    break;
        case zakonczyl : scena->update(0, 0, 800, 600);
                    break;
    }
}

void MainWindow::odbierzProsta(ProstaWiadomosc wiad)
{
    switch (wiad.typ) {

    case zakonczyl : {
            ++ileWykonal;
            ui->labelPostep->setText("Generowanie populacji -- (" + QString::number(ileWykonal) + " / " + QString::number(ileObrotow) + ")");
            ui->postep->setValue((int)(100 * (float)ileWykonal/(float)ileObrotow));
            if (ileWykonal < ileObrotow)
                nastepna();
            else {
                ileWykonal = 0;
                ui->labelPostep->setText("Zakończono generowanie populacji.");
                ui->guzikNastepna->setEnabled(true);
                ui->guzikGeneruj->setEnabled(true);
                ui->guzikSymuluj->setEnabled(true);
                ui->guzikTabela->setEnabled(true);
            }
        } break;
    }
}

void MainWindow::startSim() {
}
