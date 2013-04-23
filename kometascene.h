#ifndef KOMETASCENE_H
#define KOMETASCENE_H

#include <QGraphicsView>
#include "kometa.h"

class KometaScene : public QGraphicsView {

    Q_OBJECT

public:
    KometaScene(QWidget *parent);
    void ustawTrybGry(bool enable) { trybGry = enable; }
    void przypiszGracz(Kometa *g) { gracz = g; }

    void mouseMoveEvent(QMouseEvent *mouseEvent );
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

signals:
    void graczPuscil();

private:
    bool trybGry;
    bool drag;

    float klikX, klikY;
    float puscX, puscY;

    QGraphicsLineItem *linia;

    Kometa *gracz;
};

#endif // KOMETASCENE_H
