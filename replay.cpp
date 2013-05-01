#include "replay.h"
#include <QPainterPath>

void Replay::run()
{
    QPainterPath::Element elem;

    QTime zegar;
    zegar.start();
    int last_time, current_time;
    int ilosc = sciezka->elementCount();

    for (int i = 0; i < ilosc; ++i) {
        last_time = zegar.elapsed();

        elem = sciezka->elementAt(i);
        emit nadajWiadomosc(gracz, Wiadomosc(elem.x, elem.y, rusz));

        current_time = zegar.elapsed();

        this->thread()->msleep(qMax(FRAME_TIME - (current_time - last_time), 0.0));
    }

    emit nadajWiadomosc(gracz, Wiadomosc(0, 0, zakonczyl));
}
