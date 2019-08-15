#ifndef destinationinput_H
#define destinationinput_H

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <CommonAPI/CommonAPI.hpp>
#include "UIChinaCity.h"
#include <v1/commonapi/DestinationInputProxy.hpp>


using namespace v1_0::commonapi;
using namespace std;

namespace Ui {
class DestinationInput;
}

class Widget;

class DestinationInputWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DestinationInputWidget(Widget *parent = 0);
    ~DestinationInputWidget();

protected:
        void paintEvent(QPaintEvent *event);
private slots:
        void on_pushButton_clicked();
        void onStateComboBoxIndexChanged(int);
        void onCityComboBoxIndexChanged(int);

private:
    Ui::DestinationInput *ui;
    Widget*                                   m_Parent;
    std::shared_ptr<DestinationInputProxy<>>  myProxy;  
    UIChinaCity                               *chinaCityManager = nullptr;
    
};

#endif // destinationinput_H
