#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>
#include <QDebug>
#include "hpnetworksocket.h"

HPNetworkSocket::HPNetworkSocket(QObject *parent) :
    QObject(parent),
    currentConnectionType_(HP_TCP_SERVER),
    receivedData_(),
    toSendData_(),
    serverObject_(nullptr),
    tcpSocketToRead_(nullptr),
    tcpSocketObject_(nullptr)
{
    initialized();
}


HPNetworkSocket::~HPNetworkSocket()
{

}


bool HPNetworkSocket::createConnection(const QString& address, const QString& port, HPNetworkSocket::HP_SOCKET_TYPE socketType)
{
    bool connected = false;
    /* Sorry, we first only support TCP SERVER, and will be extended later. */
    //if(serverObject_->listen(QHostAddress(address), port.toUInt()))
    if(!serverObject_->isListening())
    {
        if(serverObject_->listen(QHostAddress::Any, 6606))
        {
            if(serverObject_->hasPendingConnections())
            {
                slotNewTcpConnected();
            }

            connected = true;
            connect(serverObject_, SIGNAL(newConnection()), this, SLOT(slotNewTcpConnected()));
        }
        else
        {
            QMessageBox::warning(nullptr, QStringLiteral("Warning"), QStringLiteral("Invalid Address or Port, sorry."));
        }
    }
    else
    {
        connected = true;
    }

    return connected;
}


const QByteArray& HPNetworkSocket::getReceivedData(void) const
{
    return receivedData_;
}


void HPNetworkSocket::slotNewTcpConnected(void)
{
    tcpSocketToRead_ = serverObject_->nextPendingConnection();

    connect(tcpSocketToRead_, SIGNAL(readyRead()), this, SLOT(slotReadData()));
}


void HPNetworkSocket::slotSendData(const QByteArray& data)
{

}


void HPNetworkSocket::slotReadData(void)
{

    receivedData_.clear();
    receivedData_ = tcpSocketToRead_->readAll();

    emit signalReadyRead();
}


void HPNetworkSocket::initialized(void)
{
    serverObject_ = new QTcpServer(this);
}
