#include "zestawienie.h"
#include "ui_zestawienie.h"
#include <QGraphicsEllipseItem>
#include <QPushButton>

Zestawienie::Zestawienie(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Zestawienie)
{
    ui->setupUi(this);

    this->setWindowTitle("Zestawienie osobników populacji");

    scena = new QGraphicsScene(0, 0, 900, 20);
    scena->setBackgroundBrush((QBrush(QColor::fromRgb(0, 0, 0), Qt::SolidPattern)));

    ui->graphicsView->setScene(scena);

    scena->addLine(0, 0, 900, 0, QPen(QColor::fromRgb(255, 255, 255)));
    scena->addLine(0, 0, 0, 20, QPen(QColor::fromRgb(255, 255, 255)));
    scena->addLine(0, 20, 900, 20, QPen(QColor::fromRgb(255, 255, 255)));
    scena->addLine(900, 0, 900, 20, QPen(QColor::fromRgb(255, 255, 255)));

}

void Zestawienie::prepareData(Populacja *pop) {

    QGridLayout *tabelka = ui->gridLayout;

    QLabel *napis[30];

    for (int i = 0; i < 30; i += 3) {
        napis[i] = new QLabel(pop->osobniki[i/3]->pozycjaString());
        napis[i + 1] = new QLabel(pop->osobniki[i/3]->kierunekString());
        napis[i + 2] = new QLabel(QString::number(pop->osobniki[i/3]->czasZycia));

        napis[i]->setAlignment(Qt::AlignCenter);
        napis[i + 1]->setAlignment(Qt::AlignCenter);
        napis[i + 2]->setAlignment(Qt::AlignCenter);

        tabelka->addWidget(napis[i], 0, (i / 3) + 1, 1, 1);
        tabelka->addWidget(napis[i + 1], 1, (i / 3) + 1, 1, 1);
        tabelka->addWidget(napis[i + 2], 2, (i / 3) + 1, 1, 1);
    }

    QGraphicsEllipseItem *kometa;
    QColor kolor;

    for (int i = 0; i < 10; ++i) {
        kolor = pop->osobniki[i]->zwrocKolor();
        kometa = new QGraphicsEllipseItem(40 + (i*90), 8, 10, 10);
        kometa->setBrush(QBrush(kolor));
        scena->addItem(kometa);
    }

    QPushButton *guzik;

    for (int i = 0; i < 10; ++i) {
        guzik = new QPushButton("Odtwórz");
        guzik->setObjectName(QString::number(i));
        connect(guzik, SIGNAL(clicked()), parentWidget(), SLOT(narysujSymulacje()));

        tabelka->addWidget(guzik, 3, i + 1, 1, 1);
    }
}

Zestawienie::~Zestawienie()
{
    delete ui;
}
