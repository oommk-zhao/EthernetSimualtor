#ifndef HPMAINCONTROLLER_H
#define HPMAINCONTROLLER_H

#include <QObject>
#include <QString>

#include "hpnetworksocket.h"

class HPNetworkDataModel;
class HPImportExportObject;
class HPMainWidget;
class QTimer;


/*

Open Application -> Import -> ImportOperator.import -> Type StringList & Data StringList *> Controller ->
Controller > Model with Type StringList & Data StringList -> Model has <Name, Type ENUM>, Enum TypeList, Data ByteArray ->
Controller > get Model Type StringList, set to the UI.

(Send)
After connected -> Time out -> UI > Type StringList & Data StringList -> Controller get Type & Data List from UI > put to Model and get the ByteArray back ->
Controller > put ByteArray to the NetworkSocket then send out.

(Receive)
After connected -> Time out -> Controller > NetworkSocket read data -> Controller get ByteArray from NetworkSocket, and put to Model then get the Data & Type StringList back ->
Controller > put Data & Type StringList to the UI, then Display.
*/


class HPMainController : public QObject
{
    Q_OBJECT
public:
    explicit HPMainController(QObject *parent = nullptr);
    virtual ~HPMainController();

    void showScreen(void);

private slots:

    void slotUpdateWidget(void);
    void slotTryToConnect(void);
    void slotTryToImport(QString fileName);
    void slotTryToExport(void);
    void slotCheckTheValidity(void);

private:

    void initialize(void);

    HPNetworkSocket::HP_SOCKET_TYPE socketType_;
    QTimer * refreshTimer_p;

    HPImportExportObject * improtExportObject_p;
    HPMainWidget * mainWidget_p;
    HPNetworkSocket * networkSocket_p;
    HPNetworkDataModel * dataModel_p;

};

#endif // HPMAINCONTROLLER_H
