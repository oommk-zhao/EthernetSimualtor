#include <QTcpServer>
#include <QMessageBox>
#include "hpnetworksocket.h"

HPNetworkSocket::HPNetworkSocket(QObject *parent) :
    QObject(parent),
    currentConnectionType_(HP_TCP_SERVER),
    serverObject_(nullptr)
{
    initialized();
}


HPNetworkSocket::~HPNetworkSocket()
{

}


void HPNetworkSocket::createConnection(const QString& address, const QString& port, HPNetworkSocket::HP_SOCKET_TYPE socketType)
{
    /* Sorry, we first only support TCP SERVER, and will be extended later. */
    if(!serverObject_->listen(QHostAddress(address), port.toUInt()))
    {
        QMessageBox::warning(nullptr, QStringLiteral("Warning"), QStringLiteral("Invalid Address or Port, sorry."));
    }
}


void HPNetworkSocket::sendData(const QByteArray& data)
{

}


QByteArray HPNetworkSocket::readData(void)
{

}


void HPNetworkSocket::initialized(void)
{
    serverObject_ = new QTcpServer(this);
}
