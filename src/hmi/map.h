#ifndef map_H
#define map_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QThread>
#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/RouteCalculationProxy.hpp>
#include <v1/commonapi/PositionProxy.hpp>
#include "dataacess.h"

using namespace v1_0::commonapi;

namespace Ui {
class Map;
}

class Widget;
class QGestureEvent;
class QPanGesture;
class QPinchGesture;
class QSwipeGesture;
class CProjectionPicture;


class MyThread : public QThread
{
public:
    MyThread();
 
protected:
    virtual void run();
 
private:
    volatile bool isStop; 
};

class MapWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MapWidget(Widget *parent = 0);
    ~MapWidget();
    
protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void on_btn_StartDemo_clicked();
    void on_btn_Up_clicked();
    void on_btn_Down_clicked();
    void on_btn_Left_clicked();
    void on_btn_Right_clicked();
    void on_btn_DemoRoute1_clicked();
    void on_btn_DemoRoute2_clicked();

    
private:
   void on_position_change(::v1::commonapi::Position::Shapepoint pos);
   void render_roads(QPainter* painter, const std::map<long, Route>& roads);
   void render_polygon(QPainter* painter, const std::map<long, Route>& roads);
   void render_vehicle(QPainter* painter);
   void render_route(QPainter* painter);
   void render_road(QPainter* painter, const Route& roads);
   void render_area(QPainter* painter, const Route& roads);
   

public:
    Ui::Map *ui;
private:
    Widget*                                  m_Parent;
    MyThread*                                m_DBThread;
    int                                      m_x_offset; 
    int                                      m_y_offset;                           
    QPixmap*                                 m_OfflinePixmap;
    QPixmap*                                 m_OfflinePolygonPixmap;    
    QPixmap*                                 m_routePixmap1;   
    QPixmap*                                 m_routePixmap2;     
    RouteCalculation::Shapepoints            m_Route;
    Position::Shapepoint                     m_CarPosition;
    std::shared_ptr<RouteCalculationProxy<>> myRouteCalcProxy;
    std::shared_ptr<PositionProxy<>>         myPosProxy;
    
 #if 0   
protected:
   // 放大/缩小
    void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;
    void mouseDoubleClickEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
 
 
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    // 平移
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
 
    bool event(QEvent *event) Q_DECL_OVERRIDE;

    void resizeEvent(QResizeEvent *e) Q_DECL_OVERRIDE;

private:
     
    bool gestureEvent(QGestureEvent *event);
    void panTriggered(QPanGesture*);
    void pinchTriggered(QPinchGesture*);
    

 
    qreal scaleFactor;
    qreal currentStepScaleFactor;
    Qt::MouseButton m_translateButton;  // 平移按钮
    bool m_bMouseTranslate;
    qreal m_zoomDelta;  // 缩放的增量
    QPoint m_lastMousePos;  // 鼠标最后按下的位置 
    
 public Q_SLOTS:
    void zoomIn(); 
    void zoomOut();  
    void zoom(float scale); 
    void translate(QPointF delta); 
  
#endif
};

#endif // map_H
