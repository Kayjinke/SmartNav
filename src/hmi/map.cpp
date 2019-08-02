#include "map.h"
#include "ui_map.h"
#include <iostream>
#include <QPainter>
#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/RouteCalculationProxy.hpp>
#include <unistd.h>

using namespace std;

using namespace v1_0::commonapi;


static std::shared_ptr<RouteCalculationProxy<>> myProxy;

MapWidget::MapWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Map)
{
    ui->setupUi(this);


}

MapWidget::~MapWidget()
{
    delete ui;
}


void MapWidget::paintEvent(QPaintEvent *event)
{
}

void MapWidget::on_btn_RouteCalculation_clicked()
{

     std::shared_ptr < CommonAPI::Runtime > runtime = CommonAPI::Runtime::get();
     std::shared_ptr<RouteCalculationProxy<>> myProxy =
     runtime->buildProxy<RouteCalculationProxy>("local", "calcRoute");

     std::cout << "Checking availability!" << std::endl;

     if (!myProxy)
     {
         cout << "this is a null pointer" << endl;
         return;
     }

     while (!myProxy->isAvailable())
         usleep(10);
     std::cout << "Available..." << std::endl;
     
     RouteCalculation::Shapepoint startpoint;
     RouteCalculation::Shapepoint endpoint;
     RouteCalculation::Shapepoints route;
     CommonAPI::CallInfo info(1000);


     CommonAPI::CallStatus callStatus;


     std::cout << "Call route with synchronous semantics ---> ..." << std::endl;
     myProxy->calcRoute(startpoint, endpoint, callStatus, route);
     for(RouteCalculation::Shapepoints::iterator iter = route.begin(); iter != route.end(); iter++)
     {
         std::cout << "route lon: " << (*iter).getLon() << " route lat:" << (*iter).getLat() << endl;
     }
     std::cout << "ddd" << std::endl;

}
