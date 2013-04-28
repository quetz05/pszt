#include "mainwindow.h"
#include <QApplication>
#include "algorytm.h"
#include <iostream>
#include <ctime>


using namespace std;

int main(int argc, char *argv[])
{
    srand(time(NULL));



    //Populacja alg();

    /*for(unsigned int i = 0; i < alg.osobniki.size(); i++ )
    {
        cout<<alg.osobniki[i]->zwrocPozycje().x<<" ";
        cout<<alg.osobniki[i]->zwrocPozycje().y<<endl;

        for(int j = 0; j<ARG; j++)
            cout<<alg.osobniki[i]->rozklady[j]<<" ";
        cout<<endl;
    }

    alg.tworzNowaPopulacje();

    cout<<endl;

    for(unsigned int i = 0; i < alg.potomki.size(); i++ )
    {
        cout<<alg.potomki[i]->zwrocPozycje().x<<" ";
        cout<<alg.potomki[i]->zwrocPozycje().y<<endl;

        for(int j = 0; j<ARG; j++)
            cout<<alg.potomki[i]->rozklady[j]<<" ";
        cout<<endl;
    }*/

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
