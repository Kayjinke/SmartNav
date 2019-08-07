#include "map.h"
#include "ui_map.h"
#include <iostream>
#include <QPainter>

#include <unistd.h>


using namespace std;


static const double axis_xmin  = -118.2156947;
static const double axis_ymax = 34.0644870;
static const double axis_xmax = -118.2000054; 
static const double axis_ymin = 34.0839314;
static const double axis_x = axis_xmax - axis_xmin;
static const double axis_y = axis_ymax - axis_ymin;
static const int screen_width = 800;
static const int screen_height = 480;

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
         myPosProxy = runtime->buildProxy<PositionProxy>("local", "Position");

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
         myRouteCalcProxy = runtime->buildProxy<RouteCalculationProxy>("local", "calcRoute");

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
         
         Position::Shapepoints pos_route;
         
         for(RouteCalculation::Shapepoints::iterator iter = route.begin(); iter != route.end(); iter++)
         {
             pos_route.push_back(Position::Shapepoint(iter->getLon(), iter->getLat()));
         }
         myPosProxy->setRoute(pos_route, callStatus);
         myPosProxy->startDemo(callStatus);
         std::cout << "ddd" << std::endl;
         
         m_Route.swap(route);
         
         update();
     }
}


struct ScreenPoint
{
    int x;
    int y;
};

void convert2screenpoint(const Wgs84Pos& from, ScreenPoint& to)
{
    to.x = (from.lon - axis_xmin) * (screen_width / axis_x); // x(lon) transformation succeed
    to.y = (-(from.lat - axis_ymax)) * (screen_height / axis_y);   // y(lat) transformation succeed  
}
  

void MapWidget::render_roads(QPainter* painter, const std::map<long, Route>& roads)
{
    for(std::map<long, Route>::const_iterator iter = roads.begin(); iter != roads.end(); iter++)
    {
         cout << "read road id : " << iter->first << " point count: " << iter->second.count << endl;
         if (iter->second.count > 2)
         {
             render_road(painter, iter->second);
         }
    } 
}

void MapWidget::render_road(QPainter* painter, const Route& roads)
{
     QPainterPath path;
     ScreenPoint pt;
     
     std::vector<Wgs84Pos>::const_iterator iter = roads.shapePoints.begin();
     
     convert2screenpoint(*iter, pt);
     
     path.moveTo(pt.x, pt.y);
            
     do
     {
         iter++;
         convert2screenpoint(*iter, pt);
         path.lineTo(pt.x, pt.y);
     }
     while(iter != roads.shapePoints.end() - 1);
     painter->drawPath(path);   
}

void MapWidget::paintEvent(QPaintEvent *event)
{
     DataRead da;
     da.road_read("routes.txt");
     
     const std::map<long, Route>& roads = da.getAllRoads();

     QPainter painter(this);
     painter.setPen(Qt::blue);
     painter.setFont(QFont("Arial", 50)); 
     
     render_roads(&painter, roads);
     
 #if 0
     
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
#endif
}
