#ifndef KOMETASCENE_H
#define KOMETASCENE_H

#include <QGraphicsView>
#include "kometa.h"

class KometaScene : public QGraphicsView {
public:
    KometaScene(QWidget *parent);
    void ustawTrybGry(bool enable) { trybGry = enable; }
    void przypiszGracz(Kometa *g) { gracz = g; }

    void mouseMoveEvent(QMouseEvent *mouseEvent );

private:
    bool trybGry;
    Kometa *gracz;
};

#endif // KOMETASCENE_H
