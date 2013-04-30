#ifndef ZESTAWIENIE_H
#define ZESTAWIENIE_H

#include <QDialog>
#include "kometa.h"
#include "algorytm.h"
#include <QGraphicsScene>

using namespace std;

namespace Ui {
class Zestawienie;
}

class Zestawienie : public QDialog
{
    Q_OBJECT
    
public:
    explicit Zestawienie(QWidget *parent = 0);
    ~Zestawienie();
    
    void prepareData(Populacja *pop);
private:
    Ui::Zestawienie *ui;
    QGraphicsScene *scena;
};

#endif // ZESTAWIENIE_H
