#include <QFile>
#include <QStringList>
#include <QString>

#include "hpcsvoperator.h"

HPCsvOperator::HPCsvOperator() :
    splitString_(";")
{

}


HPCsvOperator::~HPCsvOperator()
{

}


void HPCsvOperator::importConfigurationFile(const QString& fileName)
{
    QFile importFile(fileName);
    QByteArray fileData;

    if(importFile.open(QIODevice::ReadOnly))
    {
        while(!importFile.atEnd())
        {
            fileData = importFile.readLine();

            if(!fileData.isEmpty())
            {

            }
        }
    }


}


void HPCsvOperator::exportConfigurationFile(const QString& fileName)
{

}


void HPCsvOperator::initialize(void)
{

}
