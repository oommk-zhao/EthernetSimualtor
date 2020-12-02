#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QTabWidget>
#include <QStringList>
#include <QTimer>
#include <QFileDialog>
#include <QDebug>
#include <QChar>
#include <QGroupBox>

#include "hpmainwidget.h"


HPMainWidget::HPMainWidget(QWidget *parent)
    : QWidget(parent),
      nameIndex_(0),
      valueIndex_(1),
      defaultValueIndex_(2),
      nameLabelWidth_(100),
      nameLabelHeight_(25),
      valueLabelWidth_(165),
      valueLabelHeight_(25),
      nameValueBlockWidth_(255),
      defaultRawLabelCount_(24),
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
      projectNameLabel_p(nullptr),
      projectNameCombo_p(nullptr),
      checkButton_p(nullptr),
      resultGroupWidget_p(nullptr),
      usedChecksumNameLabel_p(nullptr),
      checkedBytesLabel_p(nullptr),
      calculatedCrcNameLabel_p(nullptr),
      calculatedCrcLabel_p(nullptr),
      expectedCrcNameLabel_p(nullptr),
      expectedCrcResultLabel_p(nullptr),
      extractedCrcNameLabel_p(nullptr),
      extractedCrcResultLabel_p(nullptr),
      extractedCountNameLabel_p(nullptr),
      extractedCountResultLabel_p(nullptr),
      localDataWidget_p(nullptr),
      rawDataWidget_p(nullptr),
      validityWidget_p(nullptr),
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
    addressLEdit_p->setText("Any");
    addressLEdit_p->setEnabled(false);

    portLabel_p = new QLabel(this);
    portLabel_p->setObjectName(QStringLiteral("portLabel_p"));
    portLabel_p->setGeometry(QRect(400, 70, 80, 25));
    portLabel_p->setText(QObject::tr("Port"));

    portLEdit_p = new QLineEdit(this);
    portLEdit_p->setObjectName(QStringLiteral("portLEdit_p"));
    portLEdit_p->setGeometry(QRect(660, 70, 50, 25));
    portLEdit_p->setText(QStringLiteral("6606"));
    portLEdit_p->setEnabled(false);

    connectionTypeComboBox_p = new QComboBox(this);
    connectionTypeComboBox_p->setObjectName(QStringLiteral("connectionTypeComboBox_p"));
    connectionTypeComboBox_p->setGeometry(QRect(165, 30, 150, 25));
    connectionTypeComboBox_p->insertItems(0, QStringList()
                                          << QObject::tr("TCP Server")
                                          << QObject::tr("TCP Socket")
                                          << QObject::tr("UDP Socket"));
    connectionTypeComboBox_p->setEnabled(false);

    refreshLabel_p = new QLabel(this);
    refreshLabel_p->setObjectName(QStringLiteral("refreshLabel_p"));
    refreshLabel_p->setGeometry(QRect(400, 110, 100, 25));
    refreshLabel_p->setText(QObject::tr("Refresh period"));

    refreshLEdit_p = new QLineEdit(this);
    refreshLEdit_p->setObjectName(QStringLiteral("refreshLEdit_p"));
    refreshLEdit_p->setGeometry(QRect(660, 110, 50, 25));
    refreshLEdit_p->setText("1000");

    connectionTypeLabel_p = new QLabel(this);
    connectionTypeLabel_p->setObjectName(QStringLiteral("connectionTypeLabel_p"));
    connectionTypeLabel_p->setGeometry(QRect(35, 30, 120, 25));
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
    exportButton_p->setEnabled(false);

    dataViewTabWidget_p = new QTabWidget(this);
    dataViewTabWidget_p->setObjectName(QStringLiteral("dataViewTabWidget_p"));
    dataViewTabWidget_p->setGeometry(QRect(35, 150, 945, 570));

    localDataWidget_p = new QWidget(dataViewTabWidget_p);
    localDataWidget_p->setObjectName(QStringLiteral("localDataWidget_p"));
    localDataWidget_p->setGeometry(0, 0, 945, 570);

    rawDataWidget_p = new QWidget(dataViewTabWidget_p);
    rawDataWidget_p->setObjectName(QStringLiteral("rawDataWidget_p"));
    rawDataWidget_p->setGeometry(0, 0, 945, 570);

    validityWidget_p = new QWidget(dataViewTabWidget_p);
    validityWidget_p->setObjectName(QStringLiteral("checksumWidget_p"));
    validityWidget_p->setGeometry(0, 0, 945, 570);

    connect(importButton_p, SIGNAL(released()), this, SLOT(slotImportReleaed()));
    connect(connectButton_p, SIGNAL(released()), this, SIGNAL(signalRequestConnect()));

    initializeRawDataWidget();
    initializeChecksumWidget();

    dataViewTabWidget_p->insertTab(dataViewTabWidget_p->count(), validityWidget_p, "Validate Received Data");
    dataViewTabWidget_p->insertTab(0, rawDataWidget_p, "TCP Raw Data");

    dataViewTabWidget_p->insertTab(1, localDataWidget_p, "TCP Server Data");

    dataViewTabWidget_p->setCurrentIndex(0);
    dataViewTabWidget_p->setEnabled(true);
    dataViewTabWidget_p->show();
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


void HPMainWidget::initializeChecksumWidget(void)
{
    projectNameLabel_p = new QLabel(validityWidget_p);
    projectNameLabel_p->setGeometry(136,15,250,50);
    projectNameLabel_p->setText(QObject::tr("Please select the Project Name:"));

    projectNameCombo_p = new QComboBox(validityWidget_p);
    projectNameCombo_p->setGeometry(395,15,200,50);
    projectNameCombo_p->insertItem(0, QObject::tr("Australia_SCGT_Loco"));

    checkButton_p = new QPushButton(validityWidget_p);
    checkButton_p->setGeometry(666,15,150,50);
    checkButton_p->setText(QObject::tr("CHECK !"));

    resultGroupWidget_p = new QGroupBox(validityWidget_p);
    resultGroupWidget_p->setGeometry(15,80,915,450);
    resultGroupWidget_p->setTitle(QObject::tr("The Result : "));

    usedChecksumNameLabel_p = new QLabel(resultGroupWidget_p);
    usedChecksumNameLabel_p->setGeometry(25,75,100,50);
    usedChecksumNameLabel_p->setText(QObject::tr("CCITT 16 Bit"));

    checkedBytesLabel_p = new QLabel(resultGroupWidget_p);
    checkedBytesLabel_p->setGeometry(250,75,300,50);
    checkedBytesLabel_p->setText(QObject::tr("From Byte 2 (count) to Byte 34 (seconds)"));

    calculatedCrcNameLabel_p = new QLabel(resultGroupWidget_p);
    calculatedCrcNameLabel_p->setGeometry(25,167,200,50);
    calculatedCrcNameLabel_p->setText(QObject::tr("Calculated CRC: "));

    calculatedCrcLabel_p = new QLabel(resultGroupWidget_p);
    calculatedCrcLabel_p->setGeometry(250,167,200,50);
    calculatedCrcLabel_p->setText(QObject::tr("Empty"));

    expectedCrcNameLabel_p = new QLabel(resultGroupWidget_p);
    expectedCrcNameLabel_p->setGeometry(25,258,200,50);
    expectedCrcNameLabel_p->setText(QObject::tr("Expected CRC in Frame: "));

    expectedCrcResultLabel_p = new QLabel(resultGroupWidget_p);
    expectedCrcResultLabel_p->setGeometry(250,258,200,50);
    expectedCrcResultLabel_p->setText(QObject::tr("Empty"));

    extractedCrcNameLabel_p = new QLabel(resultGroupWidget_p);
    extractedCrcNameLabel_p->setGeometry(25,350,200,50);
    extractedCrcNameLabel_p->setText(QObject::tr("Extracted CRC from Frame: "));

    extractedCrcResultLabel_p = new QLabel(resultGroupWidget_p);
    extractedCrcResultLabel_p->setGeometry(250,350,200,50);
    extractedCrcResultLabel_p->setText(QObject::tr("Empty"));

    /** count */
    extractedCountNameLabel_p = new QLabel(resultGroupWidget_p);
    extractedCountNameLabel_p->setGeometry(600,75,200,50);
    extractedCountNameLabel_p->setText(QObject::tr("Extracted count: "));

    extractedCountResultLabel_p = new QLabel(resultGroupWidget_p);
    extractedCountResultLabel_p->setGeometry(750,75,200,50);
    extractedCountResultLabel_p->setText(QObject::tr("Empty"));

    /** Longitude */
    extractedLongitudeNameLabel_p = new QLabel(resultGroupWidget_p);
    extractedLongitudeNameLabel_p->setGeometry(600,130,200,50);
    extractedLongitudeNameLabel_p->setText(QObject::tr("Extracted Longitude: "));

    extractedLongitudeResultLabel_p = new QLabel(resultGroupWidget_p);
    extractedLongitudeResultLabel_p->setGeometry(750,130,200,50);
    extractedLongitudeResultLabel_p->setText(QObject::tr("Empty"));

    /** Latitude */
    extractedLatitudeNameLabel_p = new QLabel(resultGroupWidget_p);
    extractedLatitudeNameLabel_p->setGeometry(600,185,200,50);
    extractedLatitudeNameLabel_p->setText(QObject::tr("Extracted Latitude: "));

    extractedLatitudeResultLabel_p = new QLabel(resultGroupWidget_p);
    extractedLatitudeResultLabel_p->setGeometry(750,185,200,50);
    extractedLatitudeResultLabel_p->setText(QObject::tr("Empty"));

    /** Altitude */
    extractedAltitudeNameLabel_p = new QLabel(resultGroupWidget_p);
    extractedAltitudeNameLabel_p->setGeometry(600,240,200,50);
    extractedAltitudeNameLabel_p->setText(QObject::tr("Extracted Altitude: "));

    extractedAltitudeResultLabel_p = new QLabel(resultGroupWidget_p);
    extractedAltitudeResultLabel_p->setGeometry(750,240,200,50);
    extractedAltitudeResultLabel_p->setText(QObject::tr("Empty"));

    /** Date */
    extractedDateNameLabel_p = new QLabel(resultGroupWidget_p);
    extractedDateNameLabel_p->setGeometry(600,295,200,50);
    extractedDateNameLabel_p->setText(QObject::tr("Extracted Date: "));
    extractedDateResultLabel_p = new QLabel(resultGroupWidget_p);
    extractedDateResultLabel_p->setGeometry(750,295,200,50);
    extractedDateResultLabel_p->setText(QObject::tr("Empty"));

    /** Time */
    extractedTimeNameLabel_p = new QLabel(resultGroupWidget_p);
    extractedTimeNameLabel_p->setGeometry(600,350,200,50);
    extractedTimeNameLabel_p->setText(QObject::tr("Extracted Time: "));
    extractedTimeResultLabel_p = new QLabel(resultGroupWidget_p);
    extractedTimeResultLabel_p->setGeometry(750,350,200,50);
    extractedTimeResultLabel_p->setText(QObject::tr("Empty"));

    connect(checkButton_p, SIGNAL(released()), this, SIGNAL(signalRequestCheckValidity()));

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
    if(byteArrayData.size() < 20) {
        return;
    }

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
            replacedStr = labelStr.replace(replaceShift, replaceCount, QString("%1").arg(byteArrayData[i] & 0xff, 2, 16, QChar('0')));
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


bool HPMainWidget::checkTheValidity(const QByteArray& rawArrayData)
{
    bool validCrc = false;
    if(projectNameCombo_p->currentText() == QStringLiteral("Australia_SCGT_Loco"))
    {
        QByteArray toCheckedArray;

        QString expectedResultStr("Empty");
        QString exactResultStr("Empty");

        if(rawArrayData.size() >= 35)
        {
            toCheckedArray = rawArrayData.mid(2, 33);
            uint16_t resultValue = crc16_ccitt(toCheckedArray);

            calculatedCrcLabel_p->setText(QString("0x%1%2")
                                          .arg(((resultValue & 0xFF00) >> 8), 2, 16, QChar('0'))
                                          .arg(((resultValue & 0x00FF) >> 0), 2, 16, QChar('0')));

            QByteArray resultByte = changeToAustraliaSCGTLoco(resultValue);

            expectedResultStr = QString("0x%1 0x%2 0x%3")
                                               .arg((resultByte[0] & 0xFF), 2, 16, QChar('0'))
                                               .arg((resultByte[1] & 0xFF), 2, 16, QChar('0'))
                                               .arg((resultByte[2] & 0xFF), 2, 16, QChar('0'));
        }

        if(rawArrayData.size() >= 38)
        {
            exactResultStr = QString("0x%1 0x%2 0x%3")
                                        .arg((rawArrayData[35] & 0xFF), 2, 16, QChar('0'))
                                        .arg((rawArrayData[36] & 0xFF), 2, 16, QChar('0'))
                                        .arg((rawArrayData[37] & 0xFF), 2, 16, QChar('0'));
            if (expectedResultStr == exactResultStr) {
                validCrc = true;
            }
        }

        expectedCrcResultLabel_p->setText(expectedResultStr);
        extractedCrcResultLabel_p->setText(exactResultStr);
    }

    return validCrc;
}

void HPMainWidget::extractValues(const QByteArray& rawArrayData) {
    /** count */
    extractedCountResultLabel_p->setText(QString("%1")
                                         .arg(rawArrayData[2], 3, 10, QChar('0')));
    /** longitude */
    QByteArray longitudeBA(rawArrayData.constData() + 3, 11);
    extractedLongitudeResultLabel_p->setText(QString::fromStdString(longitudeBA.toStdString()));
    /** latitude */
    QByteArray latitudeBA(rawArrayData.constData() + 14, 10);
    extractedLatitudeResultLabel_p->setText(QString::fromStdString(latitudeBA.toStdString()));
    /** altitude */
    QByteArray altitudeBA(rawArrayData.constData() + 24, 5);
    extractedAltitudeResultLabel_p->setText(QString::fromStdString(altitudeBA.toStdString()));
    /** date */
    extractedDateResultLabel_p->setText(QString("20%1-%2-%3")
                                        .arg(rawArrayData[29], 1, 10, QChar('0'))
                                        .arg(rawArrayData[30], 1, 10, QChar('0'))
                                        .arg(rawArrayData[31], 1, 10, QChar('0')));
    /** time */
    extractedTimeResultLabel_p->setText(QString("%1:%2:%3")
                                        .arg(rawArrayData[32], 1, 10, QChar('0'))
                                        .arg(rawArrayData[33], 1, 10, QChar('0'))
                                        .arg(rawArrayData[34], 1, 10, QChar('0')));
}

/* This shall be put into one global static class, which contains all algorithm */
uint16_t HPMainWidget::crc16_ccitt(const QByteArray& puchMsg)
{
    uint16_t wCRCin = 0xFFFF;
    uint16_t wCPoly = 0x1021;
    unsigned char wChar = 0;

    for(int i = 0; i < puchMsg.size(); i++)
    {
        wChar = puchMsg[i];
        wCRCin ^= (wChar << 8);

        for(int i = 0; i < 8; i++)
        {
            if(wCRCin & 0x8000)
            {
                wCRCin = (wCRCin << 1) ^ wCPoly;
            }
            else
            {
                wCRCin = wCRCin << 1;
            }
        }
    }

    return (wCRCin) ;
}


QByteArray HPMainWidget::changeToAustraliaSCGTLoco(uint16_t inputValue)
{
    QByteArray retArray;

    uint8_t position0 = (inputValue & 0xFE00) >> 9;
    uint8_t position1 = (inputValue & 0x01FC) >> 2;
    uint8_t position2 = (inputValue & 0x0003);

    retArray.push_back(static_cast<char>(position0));
    retArray.push_back(static_cast<char>(position1));
    retArray.push_back(static_cast<char>(position2));


    return retArray;
}

