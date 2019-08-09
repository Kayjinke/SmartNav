#include "destinationinput.h"
#include "ui_destinationinput.h"
#include <iostream>
#include <QPainter>
#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/DestinationInputProxy.hpp>
#include <unistd.h>

DestinationInputWidget::DestinationInputWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DestinationInput)
{
    ui->setupUi(this);
    setWindowTitle("DestinationInput");
    this->setAttribute(Qt::WA_DeleteOnClose,1);
}

DestinationInputWidget::~DestinationInputWidget()
{
    delete ui;
}


void DestinationInputWidget::paintEvent(QPaintEvent *event)
{
}

void DestinationInputWidget::on_btn_diback_clicked()
{
    emit sendsignal();
    this->close();
}

void DestinationInputWidget::on_pushButton_clicked()
{

     std::shared_ptr < CommonAPI::Runtime > runtime = CommonAPI::Runtime::get();
     std::shared_ptr<DestinationInputProxy<>> myProxy = runtime->buildProxy<DestinationInputProxy>("local", "destinationinput");
     std::cout << "Checking availability!" << std::endl;

     if (!myProxy)
     {
         cout << "this is a null pointer" << endl;
         return;
     }

     while (!myProxy->isAvailable())
         usleep(10);
     std::cout << "Available..." << std::endl;
    CommonAPI::CallInfo info(1000);
    CommonAPI::CallStatus callStatus;
    DestinationInput::Stringlist streets;
    std::cout << "Call getAllStreets with synchronous semantics ---> ..." << std::endl;
    myProxy->getAllStreets(callStatus, streets);
    
    for(DestinationInput::Stringlist::iterator iter = streets.begin(); iter != streets.end(); iter++)
    {
        std::cout << "street name" << *iter << endl;
        ui->listWidget->addItem(QString((*iter).c_str()));
    }
    std::cout <<"ending." << std::endl;
    


}
