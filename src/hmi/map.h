#ifndef map_H
#define map_H

#include <QWidget>

#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/RouteCalculationProxy.hpp>
#include <v1/commonapi/PositionProxy.hpp>

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
private:
    Ui::Map *ui;
    RouteCalculation::Shapepoints  m_Route;
    Position::Shapepoint           m_CarPosition;
};

#endif // map_H
