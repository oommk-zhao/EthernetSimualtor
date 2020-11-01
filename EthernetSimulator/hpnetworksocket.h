#ifndef HPNETWORKSOCKET_H
#define HPNETWORKSOCKET_H

#include <QObject>
#include <QString>

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

    void initialized(void);

    void createConnection(const QString& address, const QString& port, HPNetworkSocket::HP_SOCKET_TYPE socketType);




signals:

};

#endif // HPNETWORKSOCKET_H
