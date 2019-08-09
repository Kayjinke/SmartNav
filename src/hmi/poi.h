#ifndef POI_H
#define POI_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class Poi;
}

class PoiWidget : public QWidget
{
    Q_OBJECT
    
    
public:
    explicit PoiWidget(QWidget *parent = 0);
    ~PoiWidget();

private:
    Ui::Poi *ui;

private slots:
    //void changeSlot();
    void on_btn_back_clicked();

signals:
    void mySignal();
};

#endif // POI_H

