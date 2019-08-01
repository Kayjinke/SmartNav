#include "widget.h"
#include "destinationinput.h"
#include "ui_widget.h"
#include <iostream>
#include <QPainter>
#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/NavigationProxy.hpp>
#include <unistd.h>

using namespace std;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    
    connect(ui->btn_destinationinput, SIGNAL(clicked()), this, SLOT(on_destinationinput_btn_clicked()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::hide_all()
{
     ui->btn_destinationinput->hide();  
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
