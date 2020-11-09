#include "hpnetworkdatamodel.h"

HPNetworkDataModel::HPNetworkDataModel():
    nameIndex_(0),
    dataIndex_(1),
    typeIndex_(1),
    charDefinedStr_(QStringLiteral("Char")),
    charSizeIndex_(4),
    dataTypeMap_(),
    nameTypeMap_(),
    currentDataBox_(),
    dataTypeList_()
{
    initialize();
}


HPNetworkDataModel::~HPNetworkDataModel()
{

}


void HPNetworkDataModel::resetModel(void)
{

}


void HPNetworkDataModel::resetDataBox(void)
{

}


void HPNetworkDataModel::initializeDataTypeList(void)
{
    dataTypeMap_.clear();

    dataTypeMap_.insert("Bool", HS_BOOL);
    dataTypeMap_.insert("Unsigned_8", HS_UNSIGNED_8);
    dataTypeMap_.insert("Signed_8", HS_SIGNED_8);
    dataTypeMap_.insert("Unsigned_16", HS_UNSIGNED_16);
    dataTypeMap_.insert("Signed_16", HS_SIGNED_16);
    dataTypeMap_.insert("Unsigned_32", HS_UNSIGNED_32);
    dataTypeMap_.insert("Signed_32", HS_SIGNED_32);
    dataTypeMap_.insert("Char", HS_CHAR);
}


void HPNetworkDataModel::resetNameTypeList(const QVector<QStringList>& nameTypeList)
{
    QString varName;
    QString varType;

    nameTypeMap_.clear();
    charTypeSizeList_.clear();

    for(auto var : nameTypeList)
    {
        varName.clear();
        varType.clear();
        varName = var[nameIndex_];
        varType = var[typeIndex_];

        if(varType.contains(charDefinedStr_))
        {
            nameTypeMap_.insert(varName, HS_CHAR);
            charTypeSizeList_.push_back(varType.mid(charSizeIndex_).toInt());
        }
        else {
            nameTypeMap_.insert(varName, dataTypeMap_[varName]);
        }
    }
}


void HPNetworkDataModel::pushData(const QVector<QStringList>& dataList)
{
    currentDataBox_.clear();
    dataTypeList_.clear();

    QString varName;
    HPDataType varTypeEnum;

    QString varValue;

    QByteArray tempBytesData;

    for(auto var : dataList)
    {
        varName.clear();
        varValue.clear();
        tempBytesData.clear();

        varName = var[nameIndex_];
        varTypeEnum = nameTypeMap_[varName];

        varValue = var[dataIndex_];

        tempBytesData = getBytesData(varTypeEnum, varValue);

        if(!tempBytesData.isEmpty())
        {
            currentDataBox_.append(tempBytesData);
            dataTypeList_.push_back(varTypeEnum);
        }
    }
}


QStringList HPNetworkDataModel::getData(const QByteArray& networkData)
{
    QStringList retDataList;

    QString retStr;

    int position = 0;
    int charIndex = 0;

    for(HPDataType typeEnum : dataTypeList_)
    {
        retStr.clear();
        switch(typeEnum)
        {
        case HS_UNSIGNED_8:
        case HS_SIGNED_8: retStr = getStringData(typeEnum, networkData.mid(position, 8)); position += 8; break;
        case HS_UNSIGNED_16:
        case HS_SIGNED_16: retStr = getStringData(typeEnum, networkData.mid(position, 16)); position += 16; break;
        case HS_UNSIGNED_32:
        case HS_SIGNED_32: retStr = getStringData(typeEnum, networkData.mid(position, 32)); position += 32; break;
        case HS_BOOL: retStr = getStringData(typeEnum, networkData.mid(position, 8)); position += 8; break;
        case HS_CHAR: retStr = getStringData(typeEnum, networkData.mid(position, charTypeSizeList_[charIndex]));
                      position += charTypeSizeList_[charIndex];
                      charIndex++; break;
        default: break;
        }

        if(!retStr.isEmpty())
        {
            retDataList.push_back(retStr);
        }
    }

    return retDataList;
}


QByteArray HPNetworkDataModel::getDataBox(void)
{
    return currentDataBox_;
}


void HPNetworkDataModel::initialize(void)
{
    initializeDataTypeList();
}


QByteArray HPNetworkDataModel::getBytesData(HPDataType type, const QString& data)
{
    QByteArray retArray;

    switch(type)
    {
    case HS_UNSIGNED_8: retArray = strToCharU8(data);break;
    case HS_SIGNED_8: retArray = strToCharI8(data);break;
    case HS_UNSIGNED_16: retArray = strToCharU16(data);break;
    case HS_SIGNED_16: retArray = strToCharI16(data);break;
    case HS_UNSIGNED_32: retArray = strToCharU32(data);break;
    case HS_SIGNED_32: retArray = strToCharI32(data);break;
    case HS_BOOL: retArray = strToCharBool(data);break;
    case HS_CHAR: retArray = strToChar(data);break;
    default: break;
    }

    return retArray;
}


QString HPNetworkDataModel::getStringData(HPDataType type, const QByteArray& data)
{
    QString retStr;

    switch(type)
    {
    case HS_UNSIGNED_8: retStr = U8ToStr(data); break;
    case HS_SIGNED_8: retStr = I8ToStr(data); break;
    case HS_UNSIGNED_16: retStr = U16ToStr(data); break;
    case HS_SIGNED_16: retStr = I16ToStr(data); break;
    case HS_UNSIGNED_32: retStr = U32ToStr(data); break;
    case HS_SIGNED_32: retStr = I32ToStr(data); break;
    case HS_BOOL: retStr = BoolToStr(data); break;
    case HS_CHAR: retStr = CharToStr(data); break;
    default: break;
    }

    return retStr;
}


QByteArray HPNetworkDataModel::strToCharU8(const QString& str)
{
    QByteArray retArray;

    retArray.append(static_cast<char>(str.toUInt()));

    return retArray;
}


QByteArray HPNetworkDataModel::strToCharI8(const QString& str)
{
    QByteArray retArray;

    retArray.append(static_cast<char>(str.toInt()));

    return retArray;
}


QByteArray HPNetworkDataModel::strToCharU16(const QString& str)
{
    QByteArray retArray;

    retArray.append(static_cast<char>(str.toUInt() >> 8));
    retArray.append(static_cast<char>(str.toUInt()));


    return retArray;
}


QByteArray HPNetworkDataModel::strToCharI16(const QString& str)
{
    QByteArray retArray;

    retArray.append(static_cast<char>(str.toInt() >> 8));
    retArray.append(static_cast<char>(str.toInt()));


    return retArray;
}


QByteArray HPNetworkDataModel::strToCharU32(const QString& str)
{
    QByteArray retArray;

    retArray.append(static_cast<char>(str.toUInt() >> 8));
    retArray.append(static_cast<char>(str.toUInt()));

    retArray.append(static_cast<char>(str.toUInt() >> 24));
    retArray.append(static_cast<char>(str.toUInt() >> 16));


    return retArray;
}


QByteArray HPNetworkDataModel::strToCharI32(const QString& str)
{
    QByteArray retArray;

    retArray.append(static_cast<char>(str.toInt() >> 8));
    retArray.append(static_cast<char>(str.toInt()));
    retArray.append(static_cast<char>(str.toInt() >> 24));
    retArray.append(static_cast<char>(str.toInt() >> 16));


    return retArray;
}


QByteArray HPNetworkDataModel::strToChar(const QString& str)
{
    QByteArray retArray;

    retArray.append(str.toStdString().c_str());

    return retArray;
}


QByteArray HPNetworkDataModel::strToCharBool(const QString& str)
{
    QByteArray retArray;

    /* Not supported in the first version */

    return retArray;
}


QString HPNetworkDataModel::U8ToStr(const QByteArray& byteData)
{
    QString retStr;

    retStr = QStringLiteral("%1").arg(static_cast<uint8_t>(byteData[0]));

    return retStr;
}


QString HPNetworkDataModel::I8ToStr(const QByteArray& byteData)
{
    QString retStr;

    retStr = QStringLiteral("%1").arg(static_cast<int8_t>(byteData[0]));

    return retStr;
}


QString HPNetworkDataModel::U16ToStr(const QByteArray& byteData)
{
    QString retStr;

    uint16_t retVar = 0;
    retVar = static_cast<uint8_t>(byteData[1]) +
             (static_cast<uint8_t>(byteData[0]) << 8);

    retStr = QStringLiteral("%1").arg(retVar);

    return retStr;
}


QString HPNetworkDataModel::I16ToStr(const QByteArray& byteData)
{
    QString retStr;

    uint16_t retVar = 0;
    retVar = static_cast<uint8_t>(byteData[1]) +
             (static_cast<uint8_t>(byteData[0]) << 8);

    retStr = QStringLiteral("%1").arg(static_cast<int16_t>(retVar));

    return retStr;
}


QString HPNetworkDataModel::U32ToStr(const QByteArray& byteData)
{
    QString retStr;

    uint32_t retVar = 0;
    retVar = static_cast<uint8_t>(byteData[1]) +
             (static_cast<uint8_t>(byteData[0]) << 8) +
            (static_cast<uint8_t>(byteData[3]) << 16) +
            (static_cast<uint8_t>(byteData[2]) << 24);

    retStr = QStringLiteral("%1").arg(retVar);

    return retStr;
}


QString HPNetworkDataModel::I32ToStr(const QByteArray& byteData)
{
    QString retStr;

    uint32_t retVar = 0;
    retVar = static_cast<uint8_t>(byteData[1]) +
             (static_cast<uint8_t>(byteData[0]) << 8) +
            (static_cast<uint8_t>(byteData[3]) << 16) +
            (static_cast<uint8_t>(byteData[2]) << 24);

    retStr = QStringLiteral("%1").arg(static_cast<int32_t>(retVar));

    return retStr;
}


QString HPNetworkDataModel::CharToStr(const QByteArray& byteData)
{
    QString retStr;

    retStr.append(byteData);

    return retStr;
}


QString HPNetworkDataModel::BoolToStr(const QByteArray& byteData)
{
    QString retStr;

    /* Not supported in the first version */

    return retStr;
}

