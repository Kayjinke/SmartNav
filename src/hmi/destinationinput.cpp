#include "destinationinput.h"
#include "ui_destinationinput.h"
#include "widget.h"
#include "UIChinaCity.h"
#include <iostream>
#include <QPainter>
#include <QVBoxLayout>
#include <QListView>
#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/DestinationInputProxy.hpp>
#include <unistd.h>

DestinationInputWidget::DestinationInputWidget(Widget *parent) :
    QWidget(parent),
    m_Parent(parent),
    ui(new Ui::DestinationInput)
{
    ui->setupUi(this);
    
    connect(ui->btn_diback, SIGNAL(clicked()), m_Parent, SLOT(on_btn_di_back_clicked()));
    
    chinaCityManager = new UIChinaCity(this);

    ui->m_StateComboBox->addItems(chinaCityManager->getProvinceName());
    ui->m_StateComboBox->setView(new QListView(ui->m_StateComboBox));
    ui->m_CityComboBox->setView(new QListView(ui->m_CityComboBox));
    ui->m_RegionComboBox->setView(new QListView(ui->m_RegionComboBox));

    QObject::connect(ui->m_StateComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onStateComboBoxIndexChanged(int)));
    QObject::connect(ui->m_CityComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onCityComboBoxIndexChanged(int)));

    ui->m_StateComboBox->setCurrentText("上海");
    ui->m_CityComboBox->setCurrentText("嘉定");
}

DestinationInputWidget::~DestinationInputWidget()
{
    delete ui;
}


void DestinationInputWidget::paintEvent(QPaintEvent *event)
{
}

void DestinationInputWidget::on_pushButton_clicked()
{

     std::shared_ptr < CommonAPI::Runtime > runtime = CommonAPI::Runtime::get();
     std::shared_ptr<DestinationInputProxy<>> myProxy = runtime->buildProxy<DestinationInputProxy>("local", "destinationinput");
     std::cout << "Checking availability!" << std::endl;

     if (!myProxy)
     {
         cout << "this is a null pointer" << endl;
         return;
     }

    while (!myProxy->isAvailable())
    usleep(10);
    std::cout << "Available..." << std::endl;
    CommonAPI::CallInfo info(1000);
    CommonAPI::CallStatus callStatus;
    DestinationInput::Stringlist streets;
    std::cout << "Call getAllStreets with synchronous semantics ---> ..." << std::endl;
    myProxy->getAllStreets(callStatus, streets);
    
    for(DestinationInput::Stringlist::iterator iter = streets.begin(); iter != streets.end(); iter++)
    {
        std::cout << "street name" << *iter << endl;
        ui->listWidget->addItem(QString((*iter).c_str()));
    }
    std::cout <<"ending." << std::endl;

}

void DestinationInputWidget::onStateComboBoxIndexChanged(int index)
{
    QString nProvinceName = ui->m_StateComboBox->currentText();
    QList<QString> cityNameList = chinaCityManager->getCitysName(nProvinceName);
    ui->m_CityComboBox->clear();
    ui->m_RegionComboBox->clear();
    ui->m_CityComboBox->addItems(cityNameList);
}

void DestinationInputWidget::onCityComboBoxIndexChanged(int index)
{
    QString nProvinceName = ui->m_StateComboBox->currentText();
    QString nCityName = ui->m_CityComboBox->currentText();

    QList<QString> regionNameList = chinaCityManager->getRegionsName(nProvinceName, nCityName);
    ui->m_RegionComboBox->clear();

    ui->m_RegionComboBox->addItems(regionNameList);
}

