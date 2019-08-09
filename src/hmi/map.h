#ifndef map_H
#define map_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/RouteCalculationProxy.hpp>
#include <v1/commonapi/PositionProxy.hpp>
#include "dataacess.h"

using namespace v1_0::commonapi;

namespace Ui {
class Map;
}

class Widget;
class MapWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MapWidget(Widget *parent = 0);
    ~MapWidget();
    
protected:
    void paintEvent(QPaintEvent *event);
private slots:
    void on_btn_RouteCalculation_clicked();
    void on_btn_mapback_clicked();
    void on_btn_Up_clicked();
    void on_btn_Down_clicked();
    void on_btn_Left_clicked();
    void on_btn_Right_clicked();
    void on_btn_Map_clicked();
private:
   void on_position_change(::v1::commonapi::Position::Shapepoint pos);
   void render_roads(QPainter* painter, const std::map<long, Route>& roads);
   void render_vehicle(QPainter* painter);
   void render_route(QPainter* painter);
   void render_road(QPainter* painter, const Route& roads);
public:
    Ui::Map *ui;
private:
    Widget*                                  m_Parent;

    int                                      m_x_offset; 
    int                                      m_y_offset;                           
    QPixmap*                                 m_OfflinePixmap;
    RouteCalculation::Shapepoints            m_Route;
    Position::Shapepoint                     m_CarPosition;
    std::shared_ptr<RouteCalculationProxy<>> myRouteCalcProxy;
    std::shared_ptr<PositionProxy<>>         myPosProxy;
};

#endif // map_H
