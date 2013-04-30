#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "kometascene.h"
#include "symulation.h"
#include "wiadomosc.h"
#include "algorytm.h"
#include "zestawienie.h"
#include "replay.h"

#define NUM_THREADS 50

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void ustawLiczbePlanet(int wartosc);
    void ustawMinWage(int wartosc);
    void ustawMaksWage(int wartosc);
    void ustawLiczbeObrotow(int wartosc);

    void generujPlansze();
    void graj();
    void symuluj();
    void nastepna();
    void tabela();

    void narysujSymulacje();

    void narysuj();

    void odbierzWiadomosc(Kometa *naCzym, Wiadomosc wiad);
    void odbierzProsta(ProstaWiadomosc wiad);
    void startSim();

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void ruszaj();
    void next();

private:
    Ui::MainWindow *ui;

    std::vector <Planeta*> planety;

    int ilePlanet, minWaga, maksWaga, ileObrotow, ileWykonal;
    QGraphicsScene *scena;

    Symulation *sim;
    Kometa *gracz;

    //Symulation *sim[NUM_THREADS];
    //Kometa *gracz[NUM_THREADS];

    Zestawienie *zest;

    Populacja *pop;

    int counter;
    bool pierwsza;
};

#endif // MAINWINDOW_H
