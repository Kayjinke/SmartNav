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
    //setWindowFlags (Qt::FramelessWindowHint);
    connect(ui->btn_destinationinput, SIGNAL(clicked()), this, SLOT(on_destinationinput_btn_clicked()));
    //connect(ui->btn_map, SIGNAL(clicked()), this, SLOT(on_routecalculation_btn_clicked()));
    connect(ui->btn_POI, SIGNAL(clicked()), this, SLOT(on_Poi_btn_clicked()));

   
    QImage *image= new QImage("../image/background.jpg");  
    m_Background = QPixmap::fromImage(*image);
  
    m_MapWidget = new MapWidget(this);
    m_DestinationInputWidget = new DestinationInputWidget(this);
    m_MapWidget->hide();
    m_DestinationInputWidget->hide();

}

Widget::~Widget()
{
    delete ui;
}


void Widget::reshow()
{
    this->show();
}

void Widget::hide_all()
{
     ui->btn_destinationinput->hide(); 
     ui->btn_map->hide(); 
     ui->btn_POI->hide();
     ui->btn_weather->hide();
}


void Widget::show_all()
{
     ui->btn_destinationinput->show(); 
     ui->btn_map->show(); 
     ui->btn_POI->show();
     ui->btn_weather->show();
}

void Widget::on_btn_map_back_clicked()
{
     m_MapWidget->hide();
     show_all();
}

void Widget::on_btn_di_back_clicked()
{
     m_DestinationInputWidget->hide();
     show_all();
}

void Widget::paintEvent(QPaintEvent *event)
{
     QPainter painter(this);   
     painter.drawPixmap(0, 0, m_Background);
}

void Widget::on_destinationinput_btn_clicked()
{
     hide_all();
     m_DestinationInputWidget  = new DestinationInputWidget(this);
     m_DestinationInputWidget->show();
}

void Widget::on_btn_map_clicked()
{

     hide_all();
     m_MapWidget = new MapWidget(this);
     m_MapWidget->show();
}


void Widget::on_Poi_btn_clicked()
{
    connect(&poiWin,SIGNAL(mySignal()),this,SLOT(tomainSlot()));
    connect(ui->btn_POI,SIGNAL(clicked()),this,SLOT(tosubSlot()));
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

