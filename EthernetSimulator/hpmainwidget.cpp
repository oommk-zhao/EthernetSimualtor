#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QTabWidget>
#include <QStringList>

#include "hpmainwidget.h"


HPMainWidget::HPMainWidget(QWidget *parent)
    : QWidget(parent),
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
      dataViewTabWidget_p(nullptr)
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
}


void HPMainWidget::showScreen(void)
{
    this->show();
}
