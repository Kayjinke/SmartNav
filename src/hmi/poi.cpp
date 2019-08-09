#include "poi.h"
#include "ui_poi.h"

PoiWidget::PoiWidget(QWidget *parent) : 
     QWidget(parent),
     ui(new Ui::Poi)
{
     ui->setupUi(this);
     //this->setAttribute(Qt::WA_DeleteOnClose,1);
     setWindowTitle("POI");
     
     
     //subButton = new QPushButton;
     //subButton->setParent(this);
     //subButton->setText("to main");
     //subButton->move(100,100);
     //subButton->resize(50,30);
    // QObject::connect(subButton,SIGNAL(clicked()),this,SLOT(changeSlot()));
     //this->resize(300,300);
     
     connect(ui->btn_back, SIGNAL(clicked()), this, SLOT(on_btn_back_clicked()));
}

PoiWidget::~PoiWidget() {}

void PoiWidget::on_btn_back_clicked()
{
    emit mySignal();
}

