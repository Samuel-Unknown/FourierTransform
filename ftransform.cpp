#include <ftransform.h>
#include <QDebug>

ftransform::ftransform(QObject *parent):QObject(parent)
{
    T = 2 * M_PI;
    w1 = 2 * M_PI / T;
}

ftransform::~ftransform()
{
}

double ftransform::periodicFunc(double t) {

//    if ((t >= -M_PI) && (t < 0))
//        return t/ M_PI + 1;
//    if ((t >= 0) && (t < M_PI))
//        return -t/M_PI + 1;

//        if ((t >= -M_PI) && (t < 0))
//            return 0;
//        if ((t >= 0) && (t < M_PI))
//            return t;

//неля
//    if ((t >= -M_PI) && (t < 0)) return 1;
//    if ((t >= 0) && (t < M_PI)) return 0;
//   return 2*cos(t/3)*cos(t);

    if ((t >= -M_PI) && (t < 0))
        return cos(t/2);
    if ((t >= 0) && (t < M_PI))
        return 0;
}

double ftransform::calc_Integral(double a, double b, int N, int  typeOfCoefficient, int n) {
    double h, result;
    h = (b - a) / N; //  шаг сетки
    result = 0.0;

    switch (typeOfCoefficient) {
    case 0:
        // a0
        for (int i = 1; i <= N; i++) {
            result += periodicFunc(a + h * (i - 0.5)); //Вычисляем в средней точке и добавляем в сумму
        }
        break;
    case 1:
        // an
        for (int i = 1; i <= N; i++) {
            result += periodicFunc(a + h * (i - 0.5)) * cos( n * w1 * (a + h * (i - 0.5)) );
        }
        break;
    case 2:
        // bn
        for (int i = 1; i <= N; i++) {
            result += periodicFunc(a + h * (i - 0.5)) * sin( n * w1 * (a + h * (i - 0.5)) );
        }
        break;
    }

    result *= h;

    return result;
}

double ftransform::calc_a0() {
    a0 = 2 / T * calc_Integral(-T/2, T/2, 100, 0, 0);
    return a0;
}

double ftransform::calc_an(int n) {
    an = 2 / T * calc_Integral(-T/2, T/2, 100, 1, n);
    //qDebug() << "a"<< n << " = " << an;
    return an;
}

double ftransform::calc_bn(int n) {
    bn = 2 / T * calc_Integral(-T/2, T/2, 100, 2, n);
    //qDebug() << "b"<< n << " = " << bn;
    return bn;
}
