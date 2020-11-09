#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QTabWidget>
#include <QStringList>
#include <QTimer>

#include "hpmainwidget.h"


HPMainWidget::HPMainWidget(QWidget *parent)
    : QWidget(parent),
      nameIndex_(0),
      valueIndex_(1),
      defaultValueIndex_(2),
      nameLabelWidth_(80),
      nameLabelHeight_(25),
      valueLabelWidth_(165),
      valueLabelHeight_(25),
      nameValueBlockWidth_(255),
      refreshTimer_p(nullptr),
      addressLabel_p(nullptr),
      addressLEdit_p(nullptr),
      portLabel_p(nullptr),
      portLEdit_p(nullptr),
      connectionTypeComboBox_p(nullptr),
      refreshLabel_p(nullptr),
      refreshLEdit_p(nullptr),
      connectionTypeLabel_p(nullptr),
      connectButton_p(nullptr),
      importButton_p(nullptr),
      exportButton_p(nullptr),
      dataViewTabWidget_p(nullptr),
      localDataWidget_p(nullptr),
      connectedSocketWidget_p(),
      localNameLabelList_(),
      localValueEditList_()
{
    this->setWindowTitle(QObject::tr("Ethernet Simulator"));
    //this->setGeometry(0, 0, 1024, 768);
    this->resize(1024, 768);
    initialize();
}


HPMainWidget::~HPMainWidget()
{
}


void HPMainWidget::initialize(void)
{
    addressLabel_p = new QLabel(this);
    addressLabel_p->setObjectName(QStringLiteral("addressLabel_p"));
    addressLabel_p->setGeometry(QRect(400, 30, 100, 25));
    addressLabel_p->setText(QObject::tr("IP Address"));

    addressLEdit_p = new QLineEdit(this);
    addressLEdit_p->setObjectName(QStringLiteral("addressLEdit_p"));
    addressLEdit_p->setGeometry(QRect(510, 30, 200, 25));

    portLabel_p = new QLabel(this);
    portLabel_p->setObjectName(QStringLiteral("portLabel_p"));
    portLabel_p->setGeometry(QRect(400, 70, 80, 25));
    portLabel_p->setText(QObject::tr("Port"));

    portLEdit_p = new QLineEdit(this);
    portLEdit_p->setObjectName(QStringLiteral("portLEdit_p"));
    portLEdit_p->setGeometry(QRect(660, 70, 50, 25));

    connectionTypeComboBox_p = new QComboBox(this);
    connectionTypeComboBox_p->setObjectName(QStringLiteral("connectionTypeComboBox_p"));
    connectionTypeComboBox_p->setGeometry(QRect(165, 30, 150, 25));
    connectionTypeComboBox_p->insertItems(0, QStringList()
                                          << QObject::tr("TCP Server")
                                          << QObject::tr("TCP Socket")
                                          << QObject::tr("UDP Socket"));

    refreshLabel_p = new QLabel(this);
    refreshLabel_p->setObjectName(QStringLiteral("refreshLabel_p"));
    refreshLabel_p->setGeometry(QRect(400, 110, 80, 25));
    refreshLabel_p->setText(QObject::tr("Refresh period"));

    refreshLEdit_p = new QLineEdit(this);
    refreshLEdit_p->setObjectName(QStringLiteral("refreshLEdit_p"));
    refreshLEdit_p->setGeometry(QRect(660, 110, 50, 25));

    connectionTypeLabel_p = new QLabel(this);
    connectionTypeLabel_p->setObjectName(QStringLiteral("connectionTypeLabel_p"));
    connectionTypeLabel_p->setGeometry(QRect(35, 30, 80, 25));
    connectionTypeLabel_p->setText(QObject::tr("Connection Type"));

    connectButton_p = new QPushButton(this);
    connectButton_p->setObjectName(QStringLiteral("connectButton_p"));
    connectButton_p->setGeometry(QRect(35, 70, 280, 65));
    connectButton_p->setText(QObject::tr("Connect"));

    importButton_p = new QPushButton(this);
    importButton_p->setObjectName(QStringLiteral("importButton_p"));
    importButton_p->setGeometry(QRect(780, 30, 200, 50));
    importButton_p->setText(QObject::tr("Import"));

    exportButton_p = new QPushButton(this);
    exportButton_p->setObjectName(QStringLiteral("exportButton_p"));
    exportButton_p->setGeometry(QRect(780, 85, 200, 50));
    exportButton_p->setText(QObject::tr("Export"));

    dataViewTabWidget_p = new QTabWidget(this);
    dataViewTabWidget_p->setObjectName(QStringLiteral("dataViewTabWidget_p"));
    dataViewTabWidget_p->setGeometry(QRect(35, 150, 945, 570));

    localDataWidget_p = new QWidget(dataViewTabWidget_p);
    localDataWidget_p->setObjectName(QStringLiteral("localDataWidget_p"));
    localDataWidget_p->setGeometry(0, 0, 945, 570);

    refreshTimer_p = new QTimer(this);

    connect(refreshTimer_p, SIGNAL(timeout()), this, SLOT(slotRefreshTimeOut()));
    connect(importButton_p, SIGNAL(released()), this, SIGNAL(singalRequestImport));
    connect(connectButton_p, SIGNAL(released()), this, SLOT(slotConnectButtonReleased()));
}


void HPMainWidget::showScreen(void)
{
    this->show();
}


void HPMainWidget::initializeLocalDataWidget(const QVector<QStringList>& initializedList)
{
    QString varName;
    QString varDefaultValue;
    int count = 0;
    localValueEditList_.clear();
    localNameLabelList_.clear();

    for(auto eachList : initializedList)
    {
        varName.clear();
        varDefaultValue.clear();

        for(auto var : eachList)
        {
            varName = var.at(nameIndex_);
            varDefaultValue = var.at(defaultValueIndex_);

            QLabel * varNameLabel = new QLabel(localDataWidget_p);
            varNameLabel->setGeometry(45 + (count * (nameValueBlockWidth_ + 45)) ,
                                                                10 + (count * (nameLabelHeight_ + 10)),
                                                                nameLabelWidth_, nameLabelHeight_);
            varNameLabel->setText(varName);
            varNameLabel->setObjectName(varName);

            QLineEdit * varValueLabel = new QLineEdit(localDataWidget_p);
            varNameLabel->setGeometry(45 + nameLabelWidth_ + 5 + (count * (nameValueBlockWidth_ + 45)) ,
                                                                10 + (count * (valueLabelHeight_ + 10)),
                                                                valueLabelWidth_, valueLabelHeight_);
            varValueLabel->setText(varDefaultValue);
            varValueLabel->setObjectName((varName +QStringLiteral("Value")));

            localNameLabelList_.push_back(varName);
            localValueEditList_.push_back(varValueLabel);
        }

        ++count;
    }
}


void HPMainWidget::updateWidget(const QStringList& dataList)
{
    if(dataList.size() == localValueEditList_.size())
    {
        for(int i = 0; i < localValueEditList_.size(); i++)
        {
            localValueEditList_[i]->setText(dataList.at(i));
        }
    }
}


void HPMainWidget::pushRawData(const QByteArray& byteArrayData)
{

}


QVector<QStringList> HPMainWidget::getDataList(void)
{
    QVector<QStringList> retList;

    QStringList dataList;

    for(int i = 0; i < localNameLabelList_.size(); i++)
    {
        dataList.clear();

        dataList.push_back(localNameLabelList_[i]);
        dataList.push_back(localValueEditList_[i]->text());

        retList.push_back(dataList);
    }

    return retList;
}


void HPMainWidget::slotConnectButtonReleased(void)
{

}


void HPMainWidget::slotRefreshTimeOut(void)
{

}
