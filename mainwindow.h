#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "kometascene.h"
#include "symulation.h"
#include "wiadomosc.h"

#define NUM_THREADS 20

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

    void generujPlansze();
    void graj();
    void symuluj();
    void nastepna();
    void tabela() {}

    void odbierzWiadomosc(Kometa *naCzym, Wiadomosc wiad);
    void startSim();

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void ruszaj();

private:
    Ui::MainWindow *ui;

    std::vector <Planeta*> planety;

    int ilePlanet, minWaga, maksWaga;
    QGraphicsScene *scena;

    Symulation *sim[NUM_THREADS];
    Kometa *gracz[NUM_THREADS];

    int counter;
    bool pierwsza;
};

#endif // MAINWINDOW_H
