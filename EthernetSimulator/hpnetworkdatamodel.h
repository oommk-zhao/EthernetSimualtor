#ifndef HPNETWORKDATAMODEL_H
#define HPNETWORKDATAMODEL_H

#include <QStringList>
#include <QByteArray>
#include <QVector>
#include <QMap>

class HPNetworkDataModel
{
public:

    enum HPDataType
    {
        HS_UNSIGNED_8 = 0,
        HS_SIGNED_8,
        HS_UNSIGNED_16,
        HS_SIGNED_16,
        HS_UNSIGNED_32,
        HS_SIGNED_32,
        HS_BOOL,
        HS_CHAR

    };

    HPNetworkDataModel();
    ~HPNetworkDataModel();

    void resetModel(void);
    void resetDataBox(void);

    void initializeDataTypeList(void);

    void resetNameTypeList(const QVector<QStringList>& nameTypeList);

    void pushData(const QVector<QStringList>& dataList);
    QStringList getData(const QByteArray& networkData);

    QByteArray getDataBox(void);

private:

    void initialize(void);
    QByteArray getBytesData(HPDataType type, const QString& data);
    QString getStringData(HPDataType type, const QByteArray& data);

    QByteArray strToCharU8(const QString& str);
    QByteArray strToCharI8(const QString& str);
    QByteArray strToCharU16(const QString& str);
    QByteArray strToCharI16(const QString& str);
    QByteArray strToCharU32(const QString& str);
    QByteArray strToCharI32(const QString& str);
    QByteArray strToChar(const QString& str);
    QByteArray strToCharBool(const QString& str);

    QString U8ToStr(const QByteArray& byteData);
    QString I8ToStr(const QByteArray& byteData);
    QString U16ToStr(const QByteArray& byteData);
    QString I16ToStr(const QByteArray& byteData);
    QString U32ToStr(const QByteArray& byteData);
    QString I32ToStr(const QByteArray& byteData);
    QString CharToStr(const QByteArray& byteData);
    QString BoolToStr(const QByteArray& byteData);

    /* To be improved, we have two copies in csv operator and here, these can be moved to only one global side */
    /* Improve in next version,  yes, next. */
    const int nameIndex_;
    const int dataIndex_;
    const int typeIndex_;
    const QString charDefinedStr_;
    const int charSizeIndex_;

    QMap<QString, HPDataType> dataTypeMap_;
    QMap<QString, HPDataType> nameTypeMap_;

    /*
     * In the first version, we assume that all data are single in each byte,
     * which means in each single byte at most will have only one data.
     */
    QByteArray currentDataBox_;
    QVector<HPDataType> dataTypeList_;

    /* Sorry, we have to hardcode for the type char[*] */
    /* The count is Byte */
    QVector<int> charTypeSizeList_;
};

#endif // HPNETWORKDATAPACKAGE_H
