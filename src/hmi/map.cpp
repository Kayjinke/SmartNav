#include "map.h"
#include "ui_map.h"
#include <iostream>
#include <QPainter>

#include <unistd.h>


using namespace std;


static const double axis_xmin  = -118.21228;
static const double axis_ymax = 34.07353;
static const double axis_xmax = -118.19955; 
static const double axis_ymin = 34.07951;
static const double axis_x = axis_xmax - axis_xmin;
static const double axis_y = axis_ymax - axis_ymin;
static const int screen_width = 800;
static const int screen_height = 480;

MapWidget::MapWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Map),
    m_x_offset(0),
    m_y_offset(0)
{
    ui->setupUi(this);
    
    connect(ui->btn_Up, SIGNAL(clicked()), this, SLOT(on_btn_Up_clicked()));
    
    m_OfflinePixmap = new QPixmap(QSize(800 * 2, 480 * 2));
    m_OfflinePixmap->fill(Qt::transparent);
}

MapWidget::~MapWidget()
{
    delete ui;
    delete m_OfflinePixmap;
}

void MapWidget::on_btn_mapback_clicked()
{
    close();
    
}

void MapWidget::on_btn_Up_clicked()
{
    m_y_offset += 5;
    update();
}

void MapWidget::on_position_change(::v1::commonapi::Position::Shapepoint pos)
{
     cout << "pos lon: " << pos.getLon() << " lat: " << pos.getLat() << endl;
}

void MapWidget::on_btn_RouteCalculation_clicked()
{

     DataRead da;
     da.road_read("../data/routes.txt");
     
     const std::map<long, Route>& roads = da.getAllRoads();
     QPainter offine_painter(m_OfflinePixmap);
     render_roads(&offine_painter, roads);
     
     update();
     #if 0
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
     #endif
}


struct ScreenPoint
{
    double x;
    double y;
};

void convert2screenpoint(const Wgs84Pos& from, ScreenPoint& to)
{
    to.x = (from.lon - axis_xmin) * (screen_width / axis_x); // x(lon) transformation succeed
    to.y = (-(from.lat - axis_ymax)) * (screen_height / axis_y);   // y(lat) transformation succeed  
}
  

void MapWidget::render_roads(QPainter* painter, const std::map<long, Route>& roads)
{
    int i = 0;
    for(std::map<long, Route>::const_iterator iter = roads.begin(); iter != roads.end(); iter++, i++)
    {
         //cout << "read road id : " << iter->first << " point count: " << iter->second.count << endl;
         if (i > 100) break;
         if (iter->second.count > 2)
         {
             render_road(painter, iter->second);
         }
    } 
    cout << "draw roads end" << endl;
}

void MapWidget::render_road(QPainter* painter, const Route& roads)
{
     cout << "draw road" << endl;
     
     QPainterPath path;
     ScreenPoint pt;
     
     std::vector<Wgs84Pos>::const_iterator iter = roads.shapePoints.begin();
     
     convert2screenpoint(*iter, pt);
     path.moveTo(pt.x, pt.y);
     
     cout << "move to " << pt.x << " " << pt.y << endl;
      
            
     do
     {
         iter++;
         
         convert2screenpoint(*iter, pt);
         path.lineTo(pt.x, pt.y);
         
         cout << "line to " << pt.x << " " << pt.y << endl;
     }
     while(iter != roads.shapePoints.end() - 1);
     painter->drawPath(path);   
}

void MapWidget::paintEvent(QPaintEvent *event)
{  
     cout << "paintEvent" << endl;
     QPainter painter(this);    
     painter.drawPixmap(m_x_offset, m_y_offset, *m_OfflinePixmap);
     
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
