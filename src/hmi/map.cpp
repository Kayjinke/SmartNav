#include "map.h"
#include "ui_map.h"
#include <iostream>
#include <QPainter>
#include "widget.h"
#include <iomanip>
#include <unistd.h>


using namespace std;


static const double axis_xmin  = -118.21228;// -118.2156947   -118.21228
static const double axis_ymax = 34.07951;// 34.0839314        34.07951
static const double axis_xmax = -118.19955; // -118.2000054   -118.19955
static const double axis_ymin = 34.07353;// 34.0644870        34.07353
static const double axis_x = axis_xmax - axis_xmin;
static const double axis_y = axis_ymax - axis_ymin;
static const int screen_width = 1600 ;
static const int screen_height = 900 ;


MyThread::MyThread() {}

void MyThread::run()
{
   for(;;)
   {
       //cout << "i am sleep" << endl;
       sleep(1);
   }
}

MapWidget::MapWidget(Widget *parent) :
    QWidget(parent),
    m_Parent(parent),
    ui(new Ui::Map),
    m_x_offset(0),
    m_y_offset(0)
{
    ui->setupUi(this);
  
  #if 0
    connect(ui->btn_DemoRoute1, SIGNAL(pressed()), this, SLOT(on_btn_DemoRoute1_clicked()));
    connect(ui->btn_DemoRoute2, SIGNAL(clicked()), this, SLOT(on_btn_DemoRoute2_clicked()));
    connect(ui->btn_StartDemo, SIGNAL(clicked()), this, SLOT(on_btn_StartDemo_clicked()));    
    
    connect(ui->btn_Up, SIGNAL(clicked()), this, SLOT(on_btn_Up_clicked()));
    connect(ui->btn_Left, SIGNAL(clicked()), this, SLOT(on_btn_Left_clicked()));
    connect(ui->btn_Right, SIGNAL(clicked()), this, SLOT(on_btn_Right_clicked()));
    connect(ui->btn_Down, SIGNAL(clicked()), this, SLOT(on_btn_Down_clicked()));
    #endif
    
    
    connect(ui->btn_mapback, SIGNAL(clicked()), m_Parent, SLOT(on_btn_map_back_clicked())); 
       
    m_OfflinePixmap = new QPixmap(QSize(1600 * 2, 900 * 2));
    m_OfflinePixmap->fill(Qt::transparent);

    m_OfflinePolygonPixmap = new QPixmap(QSize(1600 * 2, 900 * 2));
    m_OfflinePolygonPixmap->fill(Qt::transparent);
        
    m_routePixmap1 = new QPixmap(QSize(1600 * 2, 900 * 2));
    m_routePixmap1->fill(Qt::transparent);

    m_routePixmap2 = new QPixmap(QSize(1600 * 2, 900 * 2));
    m_routePixmap2->fill(Qt::transparent);    
    
     m_DBThread = new MyThread();
     m_DBThread->start();
    
     DataRead da;
     da.road_read("../data/routes.txt");
     
     const std::map<long, Route>& roads = da.getAllRoads();
     QPainter offline_painter(m_OfflinePixmap);
     QPainter offline_painterpolygon(m_OfflinePolygonPixmap);
     render_polygon(&offline_painterpolygon, roads);
     render_roads(&offline_painter, roads);

}

MapWidget::~MapWidget()
{
    delete ui;
    delete m_OfflinePixmap;
    delete m_OfflinePolygonPixmap;
}


void MapWidget::on_btn_Up_clicked()
{
    m_y_offset += 20;
    update();
}

void MapWidget::on_btn_Down_clicked()
{
    m_y_offset -= 20;
    
    update();
}

void MapWidget::on_btn_Left_clicked()
{
    m_x_offset += 20;
    update();
}

void MapWidget::on_btn_Right_clicked()
{
    m_x_offset -= 20;
    update();
}

void MapWidget::on_position_change(::v1::commonapi::Position::Shapepoint pos)
{
     cout << fixed;
     cout << setprecision(7) << "pos lon: " << pos.getLon() << " lat: " << pos.getLat() << endl;
     m_CarPosition = pos;
     update();
}



void MapWidget::on_btn_DemoRoute1_clicked()
{
     std::shared_ptr < CommonAPI::Runtime > runtime = CommonAPI::Runtime::get();
     if (!myRouteCalcProxy)
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
     }
     std::cout << "Call route with demo route 1 ..." << std::endl;
     RouteCalculation::Shapepoint startpoint;
     RouteCalculation::Shapepoint endpoint;
     startpoint.setLon(1);
     CommonAPI::CallInfo info(1000);

     CommonAPI::CallStatus callStatus; 
     myRouteCalcProxy->calcRoute(startpoint, endpoint, callStatus, m_Route);
     std::cout << "Call route with demo route 1 ..." << m_Route.size() << std::endl;
     
     QPainter offline_painter(m_routePixmap1);
     render_route(&offline_painter);
     update();
}

void MapWidget::on_btn_DemoRoute2_clicked()
{
     std::shared_ptr < CommonAPI::Runtime > runtime = CommonAPI::Runtime::get();
     if (!myRouteCalcProxy)
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
         

     }
     std::cout << "Call route with demo route 2 ..." << std::endl;

     RouteCalculation::Shapepoint startpoint;
     RouteCalculation::Shapepoint endpoint;
     startpoint.setLon(2);    
     cout << " lon " << startpoint.getLon() << endl;
     CommonAPI::CallInfo info(1000);

     CommonAPI::CallStatus callStatus;   
     myRouteCalcProxy->calcRoute(startpoint, endpoint, callStatus, m_Route); 
     QPainter offline_painter(m_routePixmap2);
     render_route(&offline_painter);
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

void MapWidget::on_btn_StartDemo_clicked()
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
     
               
         Position::Shapepoints pos_route;  
         
         for(RouteCalculation::Shapepoints::iterator iter = m_Route.begin(); iter != m_Route.end(); iter++)
         {
             pos_route.push_back(Position::Shapepoint(iter->getLon(), iter->getLat()));
         }
         
 		float deltaLon1 = (pos_route[2].getLon()-pos_route[1].getLon())/10;
		float deltaLat1 = (pos_route[2].getLat()-pos_route[1].getLat())/10;
		for(int i=1;i<10;i++)
	     {
			pos_route.insert(pos_route.begin()+i+1,Position::Shapepoint(pos_route[1].getLon()+deltaLon1*i, pos_route[1].getLat()+deltaLat1*i));
		}

		
		float deltaLon2 = (pos_route[16].getLon()-pos_route[15].getLon())/5;
		float deltaLat2 = (pos_route[16].getLat()-pos_route[15].getLat())/5;
		for(int i=1;i<5;i++)
	     {

			pos_route.insert(pos_route.begin()+i+15,Position::Shapepoint(pos_route[15].getLon()+deltaLon2*i, pos_route[15].getLat()+deltaLat2*i));
          }

		 float deltaLon3 = (pos_route[24].getLon()-pos_route[23].getLon())/10;
		 float deltaLat3 = (pos_route[24].getLat()-pos_route[23].getLat())/10;	 	
		 for(int i=1;i<10;i++)
	     {
			pos_route.insert(pos_route.begin()+i+23,Position::Shapepoint(pos_route[23].getLon()+deltaLon3*i, pos_route[23].getLat()+deltaLat3*i));
          }

		 float deltaLon4 = (pos_route[34].getLon()-pos_route[33].getLon())/6;
		 float deltaLat4 = (pos_route[34].getLat()-pos_route[33].getLat())/6;
		 for(int i=1;i<6;i++)
	     {
			pos_route.insert(pos_route.begin()+i+33,Position::Shapepoint(pos_route[33].getLon()+deltaLon4*i, pos_route[33].getLat()+deltaLat4*i));
          }

		 float deltaLon5 = (pos_route[42].getLon()-pos_route[41].getLon())/6;
		 float deltaLat5 = (pos_route[42].getLat()-pos_route[41].getLat())/6;
		 for(int i=1;i<6;i++)
	     {
			pos_route.insert(pos_route.begin()+i+41,Position::Shapepoint(pos_route[41].getLon()+deltaLon5*i, pos_route[41].getLat()+deltaLat5*i));
          }

	     float deltaLon6 = (pos_route[48].getLon()-pos_route[47].getLon())/4;
		 float deltaLat6 = (pos_route[48].getLat()-pos_route[47].getLat())/4;
		 for(int i=1;i<4;i++)
	     {
			pos_route.insert(pos_route.begin()+i+47,Position::Shapepoint(pos_route[47].getLon()+deltaLon6*i, pos_route[47].getLat()+deltaLat6*i));
          }
         
         CommonAPI::CallStatus callStatus;             
         myPosProxy->setRoute(pos_route, callStatus);
         myPosProxy->startDemo(callStatus);
         std::cout << "start demo" << std::endl;
         
     }
}


void MapWidget::render_roads(QPainter* painter, const std::map<long, Route>& roads)
{

    for(std::map<long, Route>::const_iterator iter = roads.begin(); iter != roads.end(); iter++)
    {

         if (iter->second.count >= 2)
         {
             if(iter->second.type == 1)
             {

                 painter->setPen(QPen(QColor(205, 193, 180), 12, Qt::SolidLine, Qt::RoundCap));
                 render_road(painter, iter->second);
             }
         }
    }   
   
    for(std::map<long, Route>::const_iterator iter = roads.begin(); iter != roads.end(); iter++)
    {
         if (iter->second.count >= 2)
         {
             if(iter->second.type == 1)
             {
                 painter->setPen(QPen(Qt::white, 10, Qt::SolidLine, Qt::RoundCap));
                 render_road(painter, iter->second);
             }
         }
    } 

    cout << "draw roads end" << endl;
}

void MapWidget::render_polygon(QPainter* painter, const std::map<long, Route>& roads)
{
    for(std::map<long, Route>::const_iterator iter = roads.begin(); iter != roads.end(); iter++)
    {

         if (iter->second.count >= 2)
         {
             if(iter->second.type == 2)
             {
                 painter->setPen(QPen(QColor(205, 193, 180), 1, Qt::SolidLine, Qt::RoundCap));
                 render_area(painter, iter->second);
             }
         }
    }
    cout << "draw polygon end" << endl;
}

void MapWidget::render_road(QPainter* painter, const Route& roads)
{
     //cout << "draw road" << endl;
     
     QPainterPath path;
     ScreenPoint pt;

     std::vector<Wgs84Pos>::const_iterator iter = roads.shapePoints.begin();
     
     convert2screenpoint(*iter, pt);
     path.moveTo(pt.x, pt.y);
     //cout << "move to " << pt.x << " " << pt.y << endl;
       
     do
     {
         iter++;
         convert2screenpoint(*iter, pt);
         path.lineTo(pt.x, pt.y);
         
         //cout << "line to " << pt.x << " " << pt.y << endl;
     }
     while(iter != roads.shapePoints.end() - 1 );
     

     painter->drawPath(path);   
}


void MapWidget::render_area(QPainter* painter, const Route& roads)
{
    QPoint *points = new QPoint[roads.shapePoints.size()] ;

    for(int i = 0; i < roads.shapePoints.size(); i++)
    {
        ScreenPoint pt;
        convert2screenpoint(roads.shapePoints[i], pt);
        points[i].setX(pt.x);
        points[i].setY(pt.y);
    }
    painter->setBrush(QColor(217, 208, 201));
    painter->drawPolygon(points, roads.shapePoints.size());   
}

void MapWidget::render_vehicle(QPainter* painter)
{
     Wgs84Pos pos(m_CarPosition.getLon(), m_CarPosition.getLat());
     ScreenPoint pt;
     convert2screenpoint(pos, pt);
     //painter->drawEllipse(pt.x - 3, pt.y - 3, 14, 14);
     QImage *image= new QImage("../image/car.png");  
     QPixmap car = QPixmap::fromImage(*image);
	 painter->drawPixmap(pt.x - 22.5,  pt.y - 30, 45, 60,car);
}

void MapWidget::render_route(QPainter* painter)
{    
     QPainterPath path;
     painter->setPen(QPen(Qt::blue, 5, Qt::SolidLine, Qt::RoundCap));
          
     if(m_Route.size() < 2)
     {
        return;
     }
     
     cout << "render_route" << endl;

     RouteCalculation::Shapepoints::iterator iter = m_Route.begin();
     ScreenPoint pt;
     convert2screenpoint(Wgs84Pos((*iter).getLon(), (*iter).getLat()), pt);
     path.moveTo(pt.x , pt.y );
            
     do
     {
         //std::cout << "route lon: " << (*iter).getLon() << " route lat:" << (*iter).getLat() << endl;
         iter++;
         convert2screenpoint(Wgs84Pos((*iter).getLon(), (*iter).getLat()), pt);
         path.lineTo(pt.x , pt.y );
     }
     while(iter != m_Route.end() - 1);
     painter->drawPath(path);
}

void MapWidget::paintEvent(QPaintEvent *event)
{  
     cout << "paintEvent" << endl;
     QPainter painter(this);   
     painter.setBrush(QColor(242, 239, 233));
     painter.drawRect(0, 0, 1600, 900);

     painter.drawPixmap(m_x_offset, m_y_offset, *m_OfflinePolygonPixmap);
     painter.drawPixmap(m_x_offset, m_y_offset, *m_OfflinePixmap);
     painter.drawPixmap(m_x_offset, m_y_offset, *m_routePixmap1);
     painter.drawPixmap(m_x_offset, m_y_offset, *m_routePixmap2);
     
     render_vehicle(&painter);

}
