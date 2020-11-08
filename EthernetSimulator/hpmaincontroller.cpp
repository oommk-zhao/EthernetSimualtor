#include <QDebug>
#include <QByteArray>
#include <QString>
#include "hpmaincontroller.h"
#include "hpmainwidget.h"

HPMainController::HPMainController(QObject *parent):
    QObject(parent),
    improtExportObject_p(nullptr),
    mainWidget_p(nullptr),
    networkSocket_p(nullptr)
{
    int i = 65534;
    char j = static_cast<char>(i);
    char k = static_cast<char>(i >> 8);

    QByteArray test;
    test.append(k);
    test.append(j);

    uint16_t testResult = 0;

    testResult = static_cast<uint8_t>(test[1]) + (static_cast<uint8_t>(test[0]) << 8);

    qDebug() << testResult << endl;
    initialize();
}


HPMainController::~HPMainController()
{

}


void HPMainController::showScreen(void)
{
    mainWidget_p->showScreen();
}


void HPMainController::initialize(void)
{
    mainWidget_p = new HPMainWidget();
}
