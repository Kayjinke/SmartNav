#include "destinationinput.h"
#include "ui_destinationinput.h"
#include <iostream>
#include <QPainter>
#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/NavigationProxy.hpp>
#include <unistd.h>

using namespace std;

using namespace v1_0::commonapi;


static std::shared_ptr<NavigationProxy<>> myProxy;

DestinationInputWidget::DestinationInputWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DestinationInput)
{
    ui->setupUi(this);


}

DestinationInputWidget::~DestinationInputWidget()
{
    delete ui;
}


void DestinationInputWidget::paintEvent(QPaintEvent *event)
{
}

void DestinationInputWidget::on_pushButton_clicked()
{

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
     
    int32_t value = 0;
    int32_t inX1 = 5;
    std::string inX2 = "abc";
    int32_t outY1;
    std::string outY2;

    CommonAPI::CallInfo info(1000);


    CommonAPI::CallStatus callStatus;
    Navigation::Stringlist streets;

    std::cout << "Call foo with synchronous semantics ---> ..." << std::endl;
    myProxy->getAllStreets(callStatus, streets);
    for(Navigation::Stringlist::iterator iter = streets.begin(); iter != streets.end(); iter++)
    {
        std::cout << "street name" << *iter << endl;
        ui->listWidget->addItem(QString((*iter).c_str()));
    }
    std::cout << "ddd" << std::endl;

}
