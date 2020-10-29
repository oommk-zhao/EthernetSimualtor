#ifndef HPNETWORKSOCKET_H
#define HPNETWORKSOCKET_H

#include <QObject>

class HPNetworkSocket : public QObject
{
    Q_OBJECT
public:
    explicit HPNetworkSocket(QObject *parent = nullptr);

signals:

};

#endif // HPNETWORKSOCKET_H
