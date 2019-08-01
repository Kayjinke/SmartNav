#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
protected:
        void paintEvent(QPaintEvent *event);
private slots:
        void on_destinationinput_btn_clicked();
        
private:
   void hide_all();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
