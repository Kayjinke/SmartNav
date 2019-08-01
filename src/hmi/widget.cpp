#include "widget.h"
#include "ui_widget.h"
#include <iostream>
#include <QPainter>
#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/NavigationProxy.hpp>
#include <unistd.h>

using namespace std;

using namespace v1_0::commonapi;


std::shared_ptr<NavigationProxy<>> myProxy;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    std::shared_ptr < CommonAPI::Runtime > runtime = CommonAPI::Runtime::get();
     std::shared_ptr<NavigationProxy<>> myProxy =
         runtime->buildProxy<NavigationProxy>("local", "navigation");

     std::cout << "Checking availability!" << std::endl;

     if (!myProxy)
     {
         cout << "this is a null pointer" << endl;
         return;
     }

     while (!myProxy->isAvailable())
         usleep(10);
     std::cout << "Available..." << std::endl;
}

Widget::~Widget()
{
    delete ui;
}


void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
      painter.drawLine(80, 100, 650, 500);
      painter.setPen(Qt::red);
      painter.drawRect(10, 10, 100, 400);
      painter.setPen(QPen(Qt::green, 5));
      painter.setBrush(Qt::blue);
      painter.drawEllipse(50, 150, 400, 200);
}

void Widget::on_pushButton_clicked()
{
    int32_t value = 0;
    int32_t inX1 = 5;
    std::string inX2 = "abc";
    int32_t outY1;
    std::string outY2;

    CommonAPI::CallInfo info(1000);


    CommonAPI::CallStatus callStatus;
    std::string returnMessage;

    std::cout << "Call foo with synchronous semantics ..." << std::endl;
    myProxy->foo(inX1, inX2, callStatus, outY1, outY2);

    ui->lineEdit->setText(QString(outY2.c_str()));
}
