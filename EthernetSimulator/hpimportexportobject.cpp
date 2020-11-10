#include "hpimportexportobject.h"
#include "hpcsvoperator.h"
#include "hpxmloperator.h"
#include <QDebug>


HPImportExportObject::HPImportExportObject(QObject *parent) :
    QObject(parent),
    csvOperator_p(nullptr),
    xmlOperator_p(nullptr)
{
    initialize();
}


HPImportExportObject::~HPImportExportObject()
{
    if(csvOperator_p != nullptr)
    {
        delete csvOperator_p;
        csvOperator_p = nullptr;
    }

    if(xmlOperator_p != nullptr)
    {
        delete xmlOperator_p;
        xmlOperator_p = nullptr;
    }
}


bool HPImportExportObject::importConfigurationFile(const QString& fileName)
{
    bool isImported = false;
    int retValue = 0;

    retValue = csvOperator_p->importConfigurationFile(fileName);

    if(retValue == 0)
    {
        isImported = true;
    }

    return isImported;
}


bool HPImportExportObject::exportConfigurationFile(const QString& fileName)
{
    bool isExported = false;

    return isExported;
}

QVector<QStringList> HPImportExportObject::getDefinedStringList(void)
{
    return csvOperator_p->getDefinedStringList();
}


void HPImportExportObject::initialize(void)
{
    csvOperator_p = new HPCsvOperator();
    xmlOperator_p = new HPXmlOperator();
}
