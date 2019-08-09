#include "map.h"
#include "ui_map.h"
#include <iostream>
#include <QPainter>
#include "widget.h"

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

MapWidget::MapWidget(Widget *parent) :
    QWidget(parent),
    m_Parent(parent),
    ui(new Ui::Map),
    m_x_offset(0),
    m_y_offset(0)
{
    ui->setupUi(this);
    setWindowTitle("Map");
    
    
    connect(ui->btn_Map, SIGNAL(clicked()), this, SLOT(on_btn_Map_clicked()));
    connect(ui->btn_Up, SIGNAL(clicked()), this, SLOT(on_btn_Up_clicked()));
    connect(ui->btn_Left, SIGNAL(clicked()), this, SLOT(on_btn_Left_clicked()));
    connect(ui->btn_Right, SIGNAL(clicked()), this, SLOT(on_btn_Right_clicked()));
  
  
    connect(ui->btn_mapback, SIGNAL(clicked()), m_Parent, SLOT(on_btn_map_back_clicked())); 
       
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

void MapWidget::on_btn_Down_clicked()
{
    m_y_offset -= 5;
    update();
}

void MapWidget::on_btn_Left_clicked()
{
    m_x_offset += 5;
    update();
}

void MapWidget::on_btn_Right_clicked()
{
    m_x_offset -= 5;
    update();
}

void MapWidget::on_position_change(::v1::commonapi::Position::Shapepoint pos)
{
     cout << "pos lon: " << pos.getLon() << " lat: " << pos.getLat() << endl;
     m_CarPosition = pos;
     repaint();
}

void MapWidget::on_btn_Map_clicked()
{
     DataRead da;
     da.road_read("../data/routes.txt");
     
     const std::map<long, Route>& roads = da.getAllRoads();
     QPainter offine_painter(m_OfflinePixmap);
     render_roads(&offine_painter, roads);
     
     update(); 
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
           std::bind(&MapWidget::on_position_change, this, std::placeholders::_1));
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
         CommonAPI::CallInfo info(1000);

         CommonAPI::CallStatus callStatus;

         std::cout << "Call route with synchronous semantics ---> ..." << std::endl;
        
         myRouteCalcProxy->calcRoute(startpoint, endpoint, callStatus, m_Route);
               
         Position::Shapepoints pos_route;  
         
         for(RouteCalculation::Shapepoints::iterator iter = m_Route.begin(); iter != m_Route.end(); iter++)
         {
             pos_route.push_back(Position::Shapepoint(iter->getLon(), iter->getLat()));
         }
            
         myPosProxy->setRoute(pos_route, callStatus);
         myPosProxy->startDemo(callStatus);
         std::cout << "start demo" << std::endl;
         update();
     }
}


void MapWidget::render_roads(QPainter* painter, const std::map<long, Route>& roads)
{
    //int i = 0;
    for(std::map<long, Route>::const_iterator iter = roads.begin(); iter != roads.end(); iter++)
    {
         //cout << "read road id : " << iter->first << " point count: " << iter->second.count << endl;
         //if (i > 100) break;
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

void MapWidget::render_vehicle(QPainter* painter)
{
     Wgs84Pos pos(m_CarPosition.getLon(), m_CarPosition.getLat());
     ScreenPoint pt;
     convert2screenpoint(pos, pt);
     painter->drawEllipse(pt.x - 3, pt.y - 3, 6, 6);
}

void MapWidget::render_route(QPainter* painter)
{    
     QPainterPath path;
     painter->setPen(QPen(Qt::blue, 5, Qt::SolidLine, Qt::RoundCap));
          
     if(m_Route.size() < 2)
     {
        return;
     }

     RouteCalculation::Shapepoints::iterator iter = m_Route.begin();
     ScreenPoint pt;
     convert2screenpoint(Wgs84Pos((*iter).getLon(), (*iter).getLat()), pt);
     path.moveTo(pt.x, pt.y);
            
     do
     {
         //std::cout << "route lon: " << (*iter).getLon() << " route lat:" << (*iter).getLat() << endl;
         iter++;
         convert2screenpoint(Wgs84Pos((*iter).getLon(), (*iter).getLat()), pt);
         path.lineTo(pt.x, pt.y);
     }
     while(iter != m_Route.end() - 1);
     painter->drawPath(path);
}

void MapWidget::paintEvent(QPaintEvent *event)
{  
     cout << "paintEvent" << endl;
     QPainter painter(this);   
     painter.drawPixmap(m_x_offset, m_y_offset, *m_OfflinePixmap);
 
     render_route(&painter);
     render_vehicle(&painter);

}
