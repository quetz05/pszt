#ifndef KOMETASCENE_H
#define KOMETASCENE_H

#include <QGraphicsScene>
#include "kometa.h"

class KometaScene : public QGraphicsScene {
public:
    KometaScene(qreal x, qreal y, qreal w, qreal h);
    void ustawTrybGry(bool enable) { trybGry = enable; }
    void przypiszGracz(Kometa *g) { gracz = g; }

private:
    bool trybGry;
    Kometa *gracz;
};

#endif // KOMETASCENE_H
