#ifndef HPNETWORKSOCKET_H
#define HPNETWORKSOCKET_H

#include <QObject>
#include <QString>
#include <QByteArray>

class QTcpServer;
class QTcpSocket;


/* First Version, only has TCP Server functionality */

class HPNetworkSocket : public QObject
{
    Q_OBJECT
public:

    enum HP_SOCKET_TYPE{
        HP_DEFAULT_SOCKET = 1,
        HP_UPD_SOCKET = 1,
        HP_TCP_SERVER = 1 << 1,
        HP_TCP_SOCKET = 1 << 2
    } ;

    explicit HPNetworkSocket(QObject *parent = nullptr);
    virtual ~HPNetworkSocket();

    bool createConnection(const QString& address, const QString& port, HPNetworkSocket::HP_SOCKET_TYPE socketType);

    const QByteArray& getReceivedData(void) const;

signals:

    void signalReadyRead(void);

private slots:

    void slotNewTcpConnected(void);

    void slotSendData(const QByteArray& data);
    void slotReadData(void);

private:

    void initialized(void);

    HP_SOCKET_TYPE currentConnectionType_;

    QByteArray receivedData_;
    QByteArray toSendData_;

    QTcpServer * serverObject_;
    QTcpSocket * tcpSocketToRead_;

    QTcpSocket * tcpSocketObject_;

};

#endif // HPNETWORKSOCKET_H
