#include "kometascene.h"
#include <QMouseEvent>
#include <QDebug>

KometaScene::KometaScene(QWidget *parent) : QGraphicsView(parent)
{
    trybGry = false;
    drag = false;
}

void KometaScene::mouseMoveEvent(QMouseEvent *mouseEvent)
{
    if (trybGry) {

        QPointF punkt = mapToScene(mouseEvent->pos().x() , mouseEvent->pos().y());

        if (!drag) {
            gracz->ustawPozycje(Vector2(punkt.x(), punkt.y()));
        } else { //drag mode = user ustawia sile uderzenia
            this->scene()->removeItem(linia);
            linia = new QGraphicsLineItem(klikX, klikY, punkt.x(), punkt.y());
            linia->setPen(QPen(QColor::fromRgb(255, 255, 255)));
            this->scene()->addItem(linia);
        }
    }

    QGraphicsView::mouseMoveEvent(mouseEvent);
}

void KometaScene::mousePressEvent(QMouseEvent *event)
{
    if (trybGry) {
        drag = true;
        QPointF punkt = mapToScene(event->pos().x() , event->pos().y());
        klikX = punkt.x();
        klikY = punkt.y();
        linia = new QGraphicsLineItem(klikX, klikY, klikX, klikY);
        this->scene()->addItem(linia);
    }

    QGraphicsView::mousePressEvent(event);
}

void KometaScene::mouseReleaseEvent(QMouseEvent *event)
{
    if (trybGry) {
        QPointF punkt = mapToScene(event->pos().x() , event->pos().y());

        puscX = punkt.x();
        puscY = punkt.y();

        this->scene()->removeItem(linia);
        trybGry = false;
        drag = false;

        qDebug() << "czysty == " << (klikX - puscX) << " :: " << (klikY - puscY);

        gracz->ustawKierunek(Vector2((klikX - puscX)/100, (klikY - puscY)/100));

        emit graczPuscil();
    }

    QGraphicsView::mouseReleaseEvent(event);
}
