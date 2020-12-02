#include <QDebug>
#include <QByteArray>
#include <QString>
#include <QTimer>

#include "hpmaincontroller.h"
#include "hpmainwidget.h"
#include "hpimportexportobject.h"
#include "hpnetworkdatamodel.h"

HPMainController::HPMainController(QObject *parent):
    QObject(parent),
    socketType_(HPNetworkSocket::HP_TCP_SERVER),
    refreshTimer_p(nullptr),
    improtExportObject_p(nullptr),
    mainWidget_p(nullptr),
    networkSocket_p(nullptr),
    dataModel_p(nullptr)
{
    initialize();
}


HPMainController::~HPMainController()
{
    if(mainWidget_p != nullptr)
    {
        delete mainWidget_p;
        mainWidget_p = nullptr;
    }

    if(improtExportObject_p != nullptr)
    {
        delete improtExportObject_p;
        improtExportObject_p = nullptr;
    }

    if(networkSocket_p != nullptr)
    {
        delete networkSocket_p;
        networkSocket_p = nullptr;
    }

    if(dataModel_p != nullptr)
    {
        delete dataModel_p;
        dataModel_p = nullptr;
    }
}


void HPMainController::showScreen(void)
{
    mainWidget_p->showScreen();
}


void HPMainController::slotUpdateWidget(void)
{
    /* in the first version, only support HP_TCP_SERVER */
    if(socketType_ == HPNetworkSocket::HP_TCP_SERVER)
    {
        QByteArray receivedData = networkSocket_p->getReceivedData();

        mainWidget_p->pushRawData(receivedData);
        mainWidget_p->updateWidget(dataModel_p->getData(receivedData));
    }
}


void HPMainController::slotTryToConnect(void)
{
    refreshTimer_p->stop();

    QString address = mainWidget_p->getIPAddress();
    QString portNumber = mainWidget_p->getPort();

    HPNetworkSocket::HP_SOCKET_TYPE connectionType = HPNetworkSocket::HP_DEFAULT_SOCKET;

    int refreshTime = mainWidget_p->getRefreshTime();

    /* Sorry, first version with hardcode, and no UDP Socket. */
    if("TCP Server"  == mainWidget_p->getConnectionType())
    {
        connectionType = HPNetworkSocket::HP_TCP_SERVER;
    }

    if("TCP Socket"  == mainWidget_p->getConnectionType())
    {
        connectionType = HPNetworkSocket::HP_TCP_SOCKET;
    }

    /* Not handle the return result in the first version. */
    if(networkSocket_p->createConnection(address, portNumber, connectionType))
    {
        refreshTimer_p->start(refreshTime);
    }
}


void HPMainController::slotTryToImport(QString fileName)
{
    if(improtExportObject_p->importConfigurationFile(fileName))
    {
        dataModel_p->initializeDataTypeList();
        dataModel_p->resetNameTypeList(improtExportObject_p->getDefinedStringList());

        mainWidget_p->initializeLocalDataWidget(improtExportObject_p->getDefinedStringList());

        dataModel_p->pushData(mainWidget_p->getDataList());
    }
}


void HPMainController::slotTryToExport(void)
{

}


void HPMainController::slotCheckTheValidity(void)
{
    mainWidget_p->checkTheValidity(networkSocket_p->getReceivedData());
}

void HPMainController::initialize(void)
{
    mainWidget_p = new HPMainWidget();
    improtExportObject_p = new HPImportExportObject();
    networkSocket_p = new HPNetworkSocket();
    dataModel_p = new HPNetworkDataModel();

    refreshTimer_p = new QTimer(this);

    connect(mainWidget_p, SIGNAL(singalRequestImport(QString)), this, SLOT(slotTryToImport(QString)));
    connect(mainWidget_p, SIGNAL(signalRequestConnect()), this, SLOT(slotTryToConnect()));
    connect(mainWidget_p, SIGNAL(signalRequestCheckValidity()), this, SLOT(slotCheckTheValidity()));
    connect(refreshTimer_p, SIGNAL(timeout()), this, SLOT(slotUpdateWidget()));

    /* Not used yet */
    /*connect(networkSocket_p, SIGNAL(signalReadyRead()), this, SLOT());*/

}
