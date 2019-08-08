#include "widget.h"
#include "destinationinput.h"
#include "map.h"
#include "poi.h"
#include "ui_widget.h"
#include <iostream>
#include <QPainter>
#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/DestinationInputProxy.hpp>
#include <v1/commonapi/RouteCalculationProxy.hpp>
#include <v1/commonapi/PositionProxy.hpp>
#include <unistd.h>

using namespace std;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("SmartNav");
    mainButton = new QPushButton(this);
    mainButton->setText("to poi");
    mainButton->resize(50,30);
    mainButton->move(100,100);
    
    connect(ui->btn_destinationinput, SIGNAL(clicked()), this, SLOT(on_destinationinput_btn_clicked()));
    connect(ui->btn_routecalculation, SIGNAL(clicked()), this, SLOT(on_routecalculation_btn_clicked()));
    connect(ui->btn_Quit, SIGNAL(clicked()), this, SLOT(on_Quit_btn_clicked()));
    
    connect(&poiWin,SIGNAL(mySignal()),this,SLOT(tomainSlot()));
    connect(mainButton,SIGNAL(clicked()),this,SLOT(tosubSlot()));
    this->resize(800,480);

    
}

Widget::~Widget()
{
    delete ui;
}

void Widget::tosubSlot()
{
    this->hide();
    poiWin.show();
}

void Widget::tomainSlot()
{
    this->show();
    poiWin.hide();
}


void Widget::hide_all()
{
     ui->btn_destinationinput->hide(); 
     ui->btn_routecalculation->hide(); 
     ui->btn_POI->hide();
     ui->btn_weather->hide();
     ui->btn_Quit->hide();
}

void Widget::paintEvent(QPaintEvent *event)
{
}

void Widget::on_destinationinput_btn_clicked()
{
     hide_all();
     QWidget* widget = new DestinationInputWidget(this);
     widget->show();
}

void Widget::on_routecalculation_btn_clicked()
{
     hide_all();
     QWidget* widget = new MapWidget(this);
     widget->show();
}

void Widget::on_Quit_btn_clicked()
{
    close();
}
