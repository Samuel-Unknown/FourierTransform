#ifndef FTRANSFORM_H
#define FTRANSFORM_H
#include <math.h>
#include <QObject>

class ftransform : public QObject {
    Q_OBJECT
private:
    double T;    // период периодической функции
    double a0;
    double an;
    double bn;
public:
    double w1; // основная частота сигнала
    ftransform(QObject *parent = 0);
    ~ftransform();
    double periodicFunc(double t);  // периодическая функция
// считает интеграл методом прямоугольников
    // N - элементарных отрезков, a - нижний предел интегрирования, b - верхний,
    // typeOfCoefficient - какой коэффициент считаем (0 - a0, 1 - an, 2 - bn)
    // n - номер гармоники
    double calc_Integral(double a, double b, int N,  int  typeOfCoefficient, int n);
    double calc_a0(); // вычисляет коэффициент a0
    double calc_an(int n); // вычисляет коэффициент an
    double calc_bn(int n); // вычисляет коэффициент bn
};

#endif // FTRANSFORM_H
