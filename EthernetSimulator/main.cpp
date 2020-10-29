#include "hpmainwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HPMainWidget w;
    w.show();
    return a.exec();
}
