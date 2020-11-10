#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QTabWidget>
#include <QStringList>
#include <QTimer>
#include <QFileDialog>
#include <QDebug>

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
      defaultRawLabelCount_(160),
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
      rawDataWidget_p(nullptr),
      connectedSocketWidget_p(),
      localNameLabelList_(),
      localValueEditList_(),
      rawDataLabelList_()
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

    rawDataWidget_p = new QWidget(dataViewTabWidget_p);
    rawDataWidget_p->setObjectName(QStringLiteral("rawDataWidget_p"));
    rawDataWidget_p->setGeometry(0, 0, 945, 570);
    rawDataWidget_p->hide();

    connect(importButton_p, SIGNAL(released()), this, SLOT(slotImportReleaed()));
    connect(connectButton_p, SIGNAL(released()), this, SIGNAL(signalRequestConnect()));

    initializeRawDataWidget();
}


void HPMainWidget::showScreen(void)
{
    this->show();
}


void HPMainWidget::initializeRawDataWidget(void)
{
    int xShift = 0;
    int yShift = 0;
    for(int i = 0; i < defaultRawLabelCount_; i++)
    {
        xShift = i % 8;
        yShift = i / 8;
        QLabel * rawLabel_p = new QLabel(rawDataWidget_p);
        rawLabel_p->setGeometry(20 + (xShift * 115 + 15), 8 + (yShift * 25 + 5), 100, 15);
        rawLabel_p->setText(QStringLiteral("0000"));
        rawLabel_p->show();
        rawDataLabelList_.push_back(rawLabel_p);
    }
}


void HPMainWidget::initializeLocalDataWidget(const QVector<QStringList>& initializedList)
{
    QString varName;
    QString varDefaultValue;

    int count = 0;
    int xShift = 0;
    int yShift = 0;

    localValueEditList_.clear();
    localNameLabelList_.clear();

    for(auto eachList : initializedList)
    {
        xShift = count % 3;
        yShift = count / 3;

        varName.clear();
        varDefaultValue.clear();

        varName = eachList.at(nameIndex_);
        varDefaultValue = eachList.at(defaultValueIndex_);

        QLabel * varNameLabel = new QLabel(localDataWidget_p);
        varNameLabel->setGeometry(45 + (xShift * (nameValueBlockWidth_ + 45)) ,
                                                            10 + (yShift * (nameLabelHeight_ + 10)),
                                                            nameLabelWidth_, nameLabelHeight_);
        varNameLabel->setText(varName);
        varNameLabel->setObjectName(varName);
        varNameLabel->show();

        QLineEdit * varValueLabel = new QLineEdit(localDataWidget_p);
        varValueLabel->setGeometry(45 + nameLabelWidth_ + 5 + (xShift * (nameValueBlockWidth_ + 45)) ,
                                                            10 + (yShift * (valueLabelHeight_ + 10)),
                                                            valueLabelWidth_, valueLabelHeight_);
        varValueLabel->setText(varDefaultValue);
        varValueLabel->setObjectName((varName +QStringLiteral("Value")));
        varValueLabel->show();

        localNameLabelList_.push_back(varName);
        localValueEditList_.push_back(varValueLabel);

        ++count;
    }

    dataViewTabWidget_p->addTab(localDataWidget_p, "TCP Server Data");
    dataViewTabWidget_p->addTab(rawDataWidget_p, "TCP Raw Data");
    localDataWidget_p->show();
    dataViewTabWidget_p->show();
}


void HPMainWidget::updateWidget(const QStringList& dataList)
{
    qDebug() << "inside updateWidget : " << dataList.size() << "              " << dataList << endl;
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
    if(byteArrayData.size() < (defaultRawLabelCount_ * 2))
    {
        int labelIndex = 0;
        int replaceShift = 0;
        int replaceCount = 2;
        QString labelStr;
        QString replacedStr;

        for(int i = 0; i < byteArrayData.size(); i++)
        {
            labelIndex = i / 2;
            replaceShift = (i % 2) * 2;

            labelStr = rawDataLabelList_[labelIndex]->text();
            replacedStr = labelStr.replace(replaceShift, replaceCount, QString("%1").arg(byteArrayData[i] & 0xff, 0, 16));
            rawDataLabelList_[labelIndex]->setText(replacedStr);
        }
    }
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


QString HPMainWidget::getIPAddress(void) const
{
    return addressLEdit_p->text();
}


QString HPMainWidget::getPort(void) const
{
    return portLEdit_p->text();
}


QString HPMainWidget::getConnectionType(void) const
{
    return connectionTypeComboBox_p->currentText();
}


int HPMainWidget::getRefreshTime(void) const
{
    int defaultTime = 1000;
    if(refreshLEdit_p->text().toInt())
    {
        defaultTime = refreshLEdit_p->text().toInt();
    }
    return defaultTime;
}


void HPMainWidget::slotImportReleaed(void)
{
    QString importFileName;
    importFileName= QFileDialog::getOpenFileName(this, QObject::tr("Open File"), "/home", "*.csv");

    if(!importFileName.isEmpty())
    {
        emit singalRequestImport(importFileName);
    }

}

