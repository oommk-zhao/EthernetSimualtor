#include "hpmaincontroller.h"
#include "hpmainwidget.h"

HPMainController::HPMainController(QObject *parent):
    QObject(parent),
    improtExportObject_p(nullptr),
    mainWidget_p(nullptr),
    networkSocket_p(nullptr)
{
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
