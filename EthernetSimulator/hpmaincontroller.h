#ifndef HPMAINCONTROLLER_H
#define HPMAINCONTROLLER_H

#include <QObject>

class HPMainController : public QObject
{
    Q_OBJECT
public:
    explicit HPMainController(QObject *parent = nullptr);

signals:

};

#endif // HPMAINCONTROLLER_H
