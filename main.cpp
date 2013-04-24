#include "mainwindow.h"
#include <QApplication>
#include "algorytm.h"
#include <iostream>
#include <ctime>


using namespace std;

int main(int argc, char *argv[])
{
    srand(time(NULL));



    Populacja alg;

    for(unsigned int i = 0; i < alg.osobniki.size(); i++ )
    {
        cout<<alg.osobniki[i]->zwrocKierunek().x<<" ";
        cout<<alg.osobniki[i]->zwrocKierunek().y<<endl;

        for(int j = 0; j<ARG; j++)
            cout<<alg.rozklady[i][j]<<" ";
        cout<<endl;
    }

    cout<<endl;

    alg.tworzSekwencje();
    alg.krzyzowanie();
    alg.tworzNowychOsobnikow();
    alg.tworzNowaPopulacje();

    for(unsigned int i = 0; i < alg.osobniki.size(); i++ )
    {
        cout<<alg.osobniki[i]->zwrocKierunek().x<<" ";
        cout<<alg.osobniki[i]->zwrocKierunek().y<<endl;
        for(int j = 0; j<ARG; j++)
            cout<<alg.rozklady[i][j]<<" ";
        cout<<endl;
    }

    cout<<endl;

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
