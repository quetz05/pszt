#include "kometascene.h"
#include <QMouseEvent>
#include <QDebug>

KometaScene::KometaScene(QWidget *parent) : QGraphicsView(parent)
{
    trybGry = false;
}

void KometaScene::mouseMoveEvent(QMouseEvent *mouseEvent)
{
    if (trybGry) {

        QPointF punkt = mapToScene(mouseEvent->pos().x() , mouseEvent->pos().y());

        gracz->ustawPozycje(Vector2(punkt.x(), punkt.y()));
    }

    QGraphicsView::mouseMoveEvent(mouseEvent);
    this->scene()->update(0, 0, 800, 600);
}
