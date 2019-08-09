#ifndef destinationinput_H
#define destinationinput_H

#include <QWidget>
#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/DestinationInputProxy.hpp>


using namespace v1_0::commonapi;
using namespace std;

namespace Ui {
class DestinationInput;
}

class DestinationInputWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DestinationInputWidget(QWidget *parent = 0);
    ~DestinationInputWidget();
protected:
        void paintEvent(QPaintEvent *event);
private slots:
        void on_pushButton_clicked();
        void on_btn_diback_clicked();

signals:
        void sendsignal();

private:
    Ui::DestinationInput *ui;
    std::shared_ptr<DestinationInputProxy<>> myProxy;
};

#endif // destinationinput_H
