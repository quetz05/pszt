#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "kometascene.h"
#include "symulation.h"

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
    void symuluj() {}
    void nastepna() {}
    void tabela() {}

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    int ilePlanet, minWaga, maksWaga;
    QGraphicsScene *scena;

    Symulation *sim;
};

#endif // MAINWINDOW_H
