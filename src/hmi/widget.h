#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
//#include "poi.h"

namespace Ui {
class Widget;
}


class MapWidget;
class DestinationInputWidget;
class MusicWidget;



class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    
protected:
        void paintEvent(QPaintEvent *event);
private slots:
        void on_btn_destinationinput_clicked();
        void on_btn_music_clicked();
        void on_btn_map_clicked();
        //void on_Poi_btn_clicked();
        void on_btn_map_back_clicked();
        void on_btn_di_back_clicked();
        void on_btn_music_back_clicked();

        
        
        void reshow();     
       // void tomainSlot();
        //void tosubSlot();
        
private:
   void hide_all();
   void show_all();

private:
    Ui::Widget*               ui;
    QPixmap                   m_Background;
    MapWidget*                m_MapWidget;
    DestinationInputWidget*   m_DestinationInputWidget;
	MusicWidget*              m_MusicWidget;
};

#endif // WIDGET_H
