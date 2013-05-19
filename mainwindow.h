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

#define MIN_TIME 500
#define MAX_TIME 10000

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
    void ustawCzas();

    void generujPlansze();
    void graj();
    void symuluj();
    void symuluj2();
    void nastepna();
    void tabela();

    void narysujSymulacje();

    void narysuj();

    void odbierzWiadomosc(Kometa *naCzym, Wiadomosc wiad);
    void odbierzProsta(ProstaWiadomosc wiad);
    void startSim();
    void ustawGuziki(bool enable);

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

    Zestawienie *zest;

    Populacja *pop;

    int counter;
    bool pierwsza;
};

#endif // MAINWINDOW_H
