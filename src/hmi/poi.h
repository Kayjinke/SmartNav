#ifndef POI_H
#define POI_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class Widget;
}

class PoiWidget : public QWidget
{
    Q_OBJECT
    
    
public:
    explicit PoiWidget(QWidget *parent = 0);
    ~PoiWidget();

private:
    QPushButton * subButton;

private slots:
    void changeSlot();

signals:
    void mySignal();
};

#endif // POI_H

