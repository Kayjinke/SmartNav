#include "map.h"
#include "ui_map.h"
#include <iostream>
#include <QPainter>

#include <unistd.h>

using namespace std;

static std::shared_ptr<RouteCalculationProxy<>> myRouteCalcProxy;
static std::shared_ptr<PositionProxy<>> myPosProxy;

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

void MapWidget::on_position_change(::v1::commonapi::Position::Shapepoint pos)
{
     cout << "pos lon: " << pos.getLon() << " lat: " << pos.getLat() << endl;
}

void MapWidget::on_btn_RouteCalculation_clicked()
{
     std::shared_ptr < CommonAPI::Runtime > runtime = CommonAPI::Runtime::get();
     {
        std::shared_ptr<PositionProxy<>> myPosProxy =
         runtime->buildProxy<PositionProxy>("local", "Position");

         std::cout << "Checking position availability!" << std::endl;

         if (!myPosProxy)
         {
             cout << "this is a null pointer" << endl;
             return;
         }

         while (!myPosProxy->isAvailable())
             usleep(10);
         cout << "PositionProxy available" << endl;
         myPosProxy->getPositionAttribute().getChangedEvent().subscribe(
           std::bind(&MapWidget::on_position_change, this, std::placeholders::_1)
         );
     }

     {
     
 
         std::shared_ptr<RouteCalculationProxy<>> myRouteCalcProxy =
         runtime->buildProxy<RouteCalculationProxy>("local", "calcRoute");

         std::cout << "Checking route availability!" << std::endl;

         if (!myRouteCalcProxy)
         {
             cout << "this is a null pointer" << endl;
             return;
         }

         while (!myRouteCalcProxy->isAvailable())
             usleep(10);
         cout << "RouteCalculationProxy available" << endl;
         
         RouteCalculation::Shapepoint startpoint;
         RouteCalculation::Shapepoint endpoint;
         RouteCalculation::Shapepoints route;
         CommonAPI::CallInfo info(1000);

         CommonAPI::CallStatus callStatus;

         std::cout << "Call route with synchronous semantics ---> ..." << std::endl;
         myRouteCalcProxy->calcRoute(startpoint, endpoint, callStatus, route);
         std::cout << "ddd" << std::endl;
         
         m_Route.swap(route);
         
         update();
     }
}

void MapWidget::paintEvent(QPaintEvent *event)
{
     QPainter painter(this);
     painter.setPen(Qt::blue);
     painter.setFont(QFont("Arial", 50));
     //painter.drawLine(100,100,500,500);
     QPainterPath path;
     
     if (m_Route.size() < 2)
     {
         return;
     }
     
     RouteCalculation::Shapepoints::iterator iter = m_Route.begin();
     path.moveTo(iter->getLon(), iter->getLat());
            
     do
     {
         //std::cout << "route lon: " << (*iter).getLon() << " route lat:" << (*iter).getLat() << endl;
         iter++;
         path.lineTo(iter->getLon(), iter->getLat());
         
        
     }
     while(iter != m_Route.end() - 1);
     painter.drawPath(path);

}
