#ifndef map_H
#define map_H

#include <QWidget>
#include <QPainter>

#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/RouteCalculationProxy.hpp>
#include <v1/commonapi/PositionProxy.hpp>

#include "dataacess.h"

using namespace v1_0::commonapi;

namespace Ui {
class Map;
}

class MapWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MapWidget(QWidget *parent = 0);
    ~MapWidget();
    
protected:
        void paintEvent(QPaintEvent *event);
private slots:
        void on_btn_RouteCalculation_clicked();
private:
   void on_position_change(::v1::commonapi::Position::Shapepoint pos);
   void render_roads(QPainter* painter, const std::map<long, Route>& roads);
   void render_road(QPainter* painter, const Route& roads);
private:
    Ui::Map *ui;
    RouteCalculation::Shapepoints  m_Route;
    Position::Shapepoint           m_CarPosition;
    std::shared_ptr<RouteCalculationProxy<>> myRouteCalcProxy;
    std::shared_ptr<PositionProxy<>> myPosProxy;
};

#endif // map_H
