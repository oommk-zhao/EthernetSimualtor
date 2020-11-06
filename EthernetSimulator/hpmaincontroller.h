#ifndef HPMAINCONTROLLER_H
#define HPMAINCONTROLLER_H

#include <QObject>

class HPImportExportObject;
class HPMainWidget;
class HPNetworkDataPackage;
class HPNetworkSocket;

class HPMainController : public QObject
{
    Q_OBJECT
public:
    explicit HPMainController(QObject *parent = nullptr);
    virtual ~HPMainController();

    void showScreen(void);

private:

    void initialize(void);

    HPImportExportObject * improtExportObject_p;
    HPMainWidget * mainWidget_p;
    HPNetworkSocket * networkSocket_p;

};

#endif // HPMAINCONTROLLER_H
