#include <graphics.h>
#include <ftransform.h>
#include <QPainter>
#include <QDebug>

MyPaint::MyPaint(QWidget *parent) // конструктор класса MyPaint наследник QWidget
    : QWidget(parent)
{
    garmonicNum = 3;
    maxGarmonic = -1;
}

MyPaint::~MyPaint()
{
}

void MyPaint::paintEvent(QPaintEvent * /*event*/)
{
    QPainter painter(this);
    QPoint *firstP = new QPoint;        // начальная точка
    QPoint *secondP = new QPoint;   // конечная точка
    ftransform * Fourier = new ftransform;
    int recSizeX = 210, recSizeY = 210;  // размер прямоугольника в котором рисуем
    double multiplyX; // масштаб оси X (*)
    double multiplyY; // масштаб оси Y (*)
    int intervalXleft;      // начало оси X
    int intervalXRight;   // конец оси X

//  рисуем фоновый прямоугольник в котором рисуем
    painter.setBrush(Qt::black);
    painter.setPen(QPen(Qt::blue, 2));
    painter.drawRect(0, 0, recSizeY, recSizeX);

// выбираем цвет для осей разных графиков
    if (typeOfGrap == "direct") {
        painter.setPen(QPen(Qt::yellow, 1));
    } else if (typeOfGrap == "afc") {
        painter.setPen(QPen(Qt::white, 1));
    } else if (typeOfGrap == "pfc") {
          painter.setPen(QPen(Qt::green, 1));
    } else {
        painter.setPen(QPen(Qt::red, 1));
    }

//    рисуем оси X и Y
    // x
    painter.drawLine(QPointF(0, recSizeY / 2), QPointF(recSizeY, recSizeY / 2));
    // y
    painter.drawLine(QPointF(recSizeX /2, 0), QPointF(recSizeX / 2, recSizeX ));


// РИСУЕМ ГРАФИКИ

    if (typeOfGrap == "origin") {

// СТРОИМ ИСХОДНЫЙ ГРАФИК ПЕРИОДИЧЕСКОЙ ФУНКЦИИ------------------------------------------------------------------------------------------
        multiplyX = 15;
        multiplyY = 50;
        painter.setPen(QPen(Qt::green, 1));        // цвет построенной функции

        intervalXleft = - M_PI;
        intervalXRight = M_PI;

        firstP->setX(recSizeX /2 + intervalXleft * multiplyX);
        firstP->setY(recSizeY / 2 - Fourier->periodicFunc(intervalXleft) * multiplyY);

        for (double i = intervalXleft + 0.1; i <= intervalXRight; i+= 0.1) {
            secondP->setX(recSizeX /2 + i * multiplyX);
            secondP->setY(recSizeY / 2  -Fourier->periodicFunc(i) * multiplyY);
            painter.drawLine(*firstP, *secondP);
            *firstP = *secondP;
        }

        // подписываем ось Y
        painter.setPen(QPen(Qt::white, 1));
        painter.drawText(recSizeX /2 - 10,  10, "S");

        double x0 = sqrt ( pow(Fourier->calc_an(0), 2) + pow(Fourier->calc_bn(0), 2) ); // амплитуда нулевой гармоники
        QString str_x0 = QString::number(x0);
        // подписываем амплитуду в точке 0
        painter.drawText(recSizeX /2 - 10, // 10 для смещения
                                 recSizeY / 2 - x0 * multiplyY,
                                 str_x0);
        // подписываем пару значений по оси X
        painter.drawText(recSizeX /2 + multiplyX * 1,  recSizeY / 2 + 10, "1");
        painter.drawText(recSizeX /2 + multiplyX * 3,  recSizeY / 2 + 10, "3");
    } else  if (typeOfGrap == "direct") {

// СТРОИМ ДЛЯ ГАРМОНИКИ------------------------------------------------------------------------------------------------------------------
        multiplyX = 15;
        multiplyY = 50;
        painter.setPen(QPen(Qt::green, 1));         // цвет построенной функции

        double S, s = 0;
        S = Fourier->calc_a0() / 2;

        intervalXleft = -100;
        intervalXRight = 100;
        double step = 0.1; // шаг по оси X

//        qDebug() << this->garmonicNum;

        for (int j = 0; j <= this->garmonicNum; j++) {
            s += Fourier->calc_an(j) * cos(j * Fourier->w1 * intervalXleft) + Fourier->calc_bn(j) * sin(j * Fourier->w1 * intervalXleft);
        }

        firstP->setX(recSizeX /2 + multiplyX * intervalXleft);
        firstP->setY(recSizeY / 2 - ((s-S)) * multiplyY);
        s = 0;

        for (double i = intervalXleft + step; i <= intervalXRight; ) {

            for (int j = 0; j <= this->garmonicNum; j++) {
                s += Fourier->calc_an(j) * cos(j * Fourier->w1 * i) + Fourier->calc_bn(j) * sin(j * Fourier->w1 * i);
            }
            secondP->setX(recSizeX /2 + multiplyX * i);
            secondP->setY(recSizeY / 2 - ((s-S)) * multiplyY);
            painter.drawLine(*firstP, *secondP);
            *firstP = *secondP;
            s = 0;
            i += step;
        }

        // подписываем ось Y
        painter.setPen(QPen(Qt::white, 1));
        painter.drawText(recSizeX /2 - 10,  10, "S");

        double x0 = sqrt ( pow(Fourier->calc_an(0), 2) + pow(Fourier->calc_bn(0), 2) ); // амплитуда нулевой гармоники
        QString str_x0 = QString::number(x0);
        // подписываем амплитуду нулевой гармоники !!
        painter.drawText(recSizeX /2 - 10, // 10 для смещения
                                 recSizeY / 2 - x0 * multiplyY,
                                 str_x0);
        // подписываем пару значений по оси X
        painter.drawText(recSizeX /2 + multiplyX * 1,  recSizeY / 2 + 10, "1");
        painter.drawText(recSizeX /2 + multiplyX * 3,  recSizeY / 2 + 10, "3");
    } else if (typeOfGrap == "afc") {

// СТРОИМ АЧХ ---------------------------------------------------------------------------------------------------------------------------------
        multiplyX = 5;
        multiplyY = 80;
        painter.setPen(QPen(Qt::red, 1));      // цвет построенной функции
        double value, oldValue = -1;              // значение амлитуды

        for (int i = 0; i <= 50; i++) { // до 50ой гармоники
            value = sqrt ( pow(Fourier->calc_an(i), 2) + pow(Fourier->calc_bn(i), 2) );

            if (i == 0) {
                this->ampOfMaxGarmonic = value;
                oldValue  = value;
            }

            painter.drawLine(recSizeX /2 + multiplyX * i,
                                     recSizeY / 2 - value * multiplyY,
                                     recSizeX /2 + multiplyX * i, recSizeY / 2);

//            qDebug() << "i: " << i;
//            qDebug() << "value: " << value;

//            if ( (value < this->ampOfMaxGarmonic * 0.1) && (oldValue > 0.1 * this->ampOfMaxGarmonic)) {
//                this->maxGarmonic = i;
//                oldValue = value;
//            } else {
//               oldValue = value;
//            }

        }
//        qDebug() << "a0 * 0.1 = " <<this->ampOfMaxGarmonic * 0.1;

        this->set_maxGarmonic(this->maxGarmonic); // выводим на экран максимальную независимую гармонику

        // подписываем ось Y
        painter.setPen(QPen(Qt::yellow, 1));
       // painter.drawText(recSizeX /2 - 10,  10, "A");

        double x0 = sqrt ( pow(Fourier->calc_an(0), 2) + pow(Fourier->calc_bn(0), 2) ); // амплитуда нулевой гармоники
        QString str_x0 = QString::number(x0);

        // подписываем амплитуду нулевой гармоники
        painter.drawText(recSizeX /2 - 10, // 10 для смещения
                                 recSizeY / 2 - x0 * multiplyY,
                                 str_x0);

        // подписываем пару значений по оси X
        painter.drawText(recSizeX /2 + multiplyX * 1,  recSizeY / 2 + 10, "1");
        painter.drawText(recSizeX /2 + multiplyX * 3,  recSizeY / 2 + 10, "3");

        painter.drawText(recSizeX /2 - 10, // 10 для смещения
                                 recSizeY / 2 - x0 * multiplyY,
                                 str_x0);

    } else if (typeOfGrap == "pfc") {

// СТРОИМ ФЧХ---------------------------------------------------------------------------------------------------------------------------------
          // меняем масштаб
          multiplyX = 5;
          multiplyY = 5;
          painter.setPen(QPen(Qt::blue, 1));        // цвет построенной функции

          for (int i = 0; i <= 50; i++) { // до 50ой гармоники
              painter.drawLine(recSizeX /2 + multiplyX * i,
                                       recSizeY / 2 - (Fourier->calc_bn(i) / Fourier->calc_an(i)) * multiplyY,
                                       recSizeX /2 + multiplyX * i, recSizeY / 2);
          }

          // подписываем ось Y
          painter.setPen(QPen(Qt::red, 1));
          painter.drawText(recSizeX /2 - 10,  10, "Ф");

          double x0 = Fourier->calc_bn(0) / Fourier->calc_an(0); // амплитуда нулевой гармоники
          QString str_x0 = QString::number(x0);

          // подписываем амплитуду нулевой гармоники
          painter.drawText(recSizeX /2 - 10, // 10 для смещения
                                   recSizeY / 2 - x0 * multiplyY,
                                   str_x0);
          // подписываем пару значений по оси X
          painter.drawText(recSizeX /2 + multiplyX * 1,  recSizeY / 2 + 10, "1");
          painter.drawText(recSizeX /2 + multiplyX * 3,  recSizeY / 2 + 10, "3");

    } else {
        painter.setPen(QPen(Qt::red, 1));
    }

    // удаляем объекты
    delete firstP;
    delete secondP;
}

void MyPaint::setTypeOfGrapic(QString type) {
    typeOfGrap = type;
}

void MyPaint::set_garmonic(int g) {
    garmonicNum = g;
}
