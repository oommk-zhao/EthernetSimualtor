#include <QFile>
#include <QDebug>

#include "hpcsvoperator.h"

HPCsvOperator::HPCsvOperator() :
    splitString_(QStringLiteral(";")),
    fileCode_(QStringLiteral("EthernetSimulatorHaslerShanghai")),
    typeIndex_(1),
    charDefinedStr_("Char"),
    charSizeIndex_(4),
    typeStringList_(),
    definedStringList_(),
    availableTypeList_(),
    availableHeadList_()
{
    initialize();
}


HPCsvOperator::~HPCsvOperator()
{

}


/*

Import > read all lines first, put into the StringList (To test the possibility, otherwise use ByteArray) ->
Check the legality of the file (Head and End) -> Split the columns and Save the data, check the Type String ->
Put the result to the Type StringList and Data StringList, finished.

*/

int HPCsvOperator::importConfigurationFile(const QString& fileName)
{
    int retValue = 0;
    QFile importFile(fileName);
    QByteArray fileData;
    QStringList toImportData;

    typeStringList_.clear();
    definedStringList_.clear();

    if(importFile.open(QIODevice::ReadOnly))
    {
        while(!importFile.atEnd())
        {
            fileData = importFile.readLine();
            fileData.replace("\n", "");

            if(!fileData.isEmpty())
            {
                toImportData.push_back(fileData);
            }
        }
    }
    else {
        retValue = -1;
    }

    if(toImportData.size() < 4)
    {
        retValue = -1;
    }

    if(retValue == 0)
    {
        QStringList fileHeadAndEnd;
        fileHeadAndEnd.push_back(toImportData.takeFirst());
        fileHeadAndEnd.push_back(toImportData.takeLast());

        if(!checkFileLegality(fileHeadAndEnd))
        {
            retValue = -2;
        }
    }

    if(retValue == 0)
    {
        if(!importData(toImportData.takeFirst(), toImportData))
        {
            retValue = -3;
        }
    }

    return retValue;
}


void HPCsvOperator::exportConfigurationFile(const QString&)
{

}


QStringList HPCsvOperator::getTypeStringList(void)
{
    return typeStringList_;
}


QVector<QStringList> HPCsvOperator::getDefinedStringList(void)
{
    return definedStringList_;
}


void HPCsvOperator::initialize(void)
{
    availableHeadList_.push_back("Name");
    availableHeadList_.push_back("Type");
    availableHeadList_.push_back("DefaultValue");

    availableTypeList_.insert("Bool");
    availableTypeList_.insert("Unsigned_8");
    availableTypeList_.insert("Signed_8");
    availableTypeList_.insert("Unsigned_16");
    availableTypeList_.insert("Signed_16");
    availableTypeList_.insert("Unsigned_32");
    availableTypeList_.insert("Signed_32");
}



bool HPCsvOperator::checkFileLegality(const QStringList& fileHeadAndEnd)
{
    bool isLegal = false;

    QStringList correctCode{fileCode_, fileCode_};

    if(fileHeadAndEnd == correctCode)
    {
        isLegal = true;
    }

    return isLegal;
}


bool HPCsvOperator::importData(const QString& csvHead, const QStringList& importData)
{
    bool isSuccess = true;
    QStringList splitedHead;
    splitedHead = csvHead.split(splitString_);

    if(splitedHead != availableHeadList_)
    {
        isSuccess = false;
    }
    else {
        typeStringList_= splitedHead;
    }

    if(isSuccess)
    {
        QStringList splitedData;
        for (auto dataVar : importData) {
            splitedData.clear();
            splitedData = dataVar.split(splitString_);

            if(splitedData.size() != splitedHead.size())
            {
                isSuccess = false;
                break;
            }

            if(splitedData[typeIndex_].contains(charDefinedStr_))
            {
                int noUse = splitedData[typeIndex_].mid(charSizeIndex_).toInt(&isSuccess, 10);
            }
            else if(!availableTypeList_.contains(splitedData[typeIndex_]))
            {
                isSuccess = false;
            }

            if(!isSuccess)
            {
                break;
            }

            definedStringList_.push_back(splitedData);
        }
    }

    return isSuccess;
}
