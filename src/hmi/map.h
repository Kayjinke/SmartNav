#ifndef map_H
#define map_H

#include <QWidget>

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
    Ui::Map *ui;
};

#endif // map_H
