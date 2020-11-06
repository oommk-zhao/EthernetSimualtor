#include "hpmaincontroller.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HPMainController mainController;
    mainController.showScreen();
    return a.exec();
}
