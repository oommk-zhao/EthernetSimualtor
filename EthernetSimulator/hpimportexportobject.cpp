#include "hpimportexportobject.h"

HPImportExportObject::HPImportExportObject(QObject *parent) :
    QObject(parent),
    csvOperator_p(nullptr),
    xmlOperator_p(nullptr)
{
    initialize();
}


HPImportExportObject::~HPImportExportObject()
{

}


void HPImportExportObject::importConfigurationFile(const QString& fileName)
{

}


void HPImportExportObject::exportConfigurationFile(const QString& fileName)
{

}


void HPImportExportObject::initialize(void)
{

}
