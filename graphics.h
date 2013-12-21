#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <QWidget>
#include <QString>

class MyPaint : public QWidget {

   Q_OBJECT // нужно ибо используем сигналы

private:
    QString typeOfGrap; // тип графика
    int garmonicNum; //номер гармоники
    int maxGarmonic; // номер наивысшей существенной гармоники
    double ampOfMaxGarmonic; // значение амплитуды для наивысшей сущ. гармоники

public:
    MyPaint(QWidget *parent = 0);
    ~MyPaint();
    void setTypeOfGrapic(QString type);

protected:
    void paintEvent(QPaintEvent * event); // обработчик события отрисовки

public slots:
    void set_garmonic(int);    // задаёт гармонику для расчёта

signals:
    int set_maxGarmonic(int);
};

#endif // GRAPHICS_H
