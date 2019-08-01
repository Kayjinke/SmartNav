#ifndef destinationinput_H
#define destinationinput_H

#include <QWidget>

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

private:
    Ui::DestinationInput *ui;
};

#endif // destinationinput_H
