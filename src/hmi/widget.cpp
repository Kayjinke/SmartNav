#include "widget.h"
#include "destinationinput.h"
#include "map.h"
#include "ui_widget.h"
#include <iostream>
#include <QPainter>
#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/NavigationProxy.hpp>
#include <v1/commonapi/RouteCalculationProxy.hpp>
#include <unistd.h>

using namespace std;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    
    connect(ui->btn_destinationinput, SIGNAL(clicked()), this, SLOT(on_destinationinput_btn_clicked()));
    
    connect(ui->btn_routecalculation, SIGNAL(clicked()), this, SLOT(on_routecalculation_btn_clicked()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::hide_all()
{
     ui->btn_destinationinput->hide(); 
     ui->btn_routecalculation->hide(); 
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
