#include "mainwindow.h"
#include "graphics.h"
#include "ftransform.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    MyPaint * directTransGrap = new MyPaint; // прямое преобразование
    MyPaint * afcGrap = new MyPaint;    // АЧХ
    MyPaint * pfcGrap = new MyPaint;   // ФЧХ
    MyPaint * originGrap = new MyPaint;   // исходная периодическая функция

// выбираем типы графиков для объектов
    directTransGrap->setTypeOfGrapic("direct");
    afcGrap->setTypeOfGrapic("afc");
    pfcGrap->setTypeOfGrapic("pfc");
    originGrap->setTypeOfGrapic("origin");

// прицепляем к макету графики
    ui->directTrGridLayout->addWidget(directTransGrap);
    ui->afcGridLayout->addWidget(afcGrap);
    ui->pfcGridLayout->addWidget(pfcGrap);
    ui->originGridLayout->addWidget(originGrap);

// связываем нажатие кнопки с перерисовкой графика
    connect(ui->pushButton, SIGNAL(clicked()), directTransGrap, SLOT(repaint()));
//  передача сигнала для изменения номера гармоники
    connect(ui->garmonica, SIGNAL(valueChanged(int)), directTransGrap, SLOT(set_garmonic(int)));
//  передача сигнала для передачи значения максимально независимой гармоники
    connect(afcGrap, SIGNAL(set_maxGarmonic(int)), ui->label, SLOT(setNum(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}
