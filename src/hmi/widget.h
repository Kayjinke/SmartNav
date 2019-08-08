#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include "poi.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

public:
    PoiWidget poiWin;
    QPushButton * mainButton;    
    
protected:
        void paintEvent(QPaintEvent *event);
private slots:
        void on_destinationinput_btn_clicked();
        void on_routecalculation_btn_clicked();
        void on_Quit_btn_clicked();
        
        void tomainSlot();
        void tosubSlot();
        
private:
   void hide_all();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
