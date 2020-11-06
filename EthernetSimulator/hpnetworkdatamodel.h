#ifndef HPNETWORKDATAMODEL_H
#define HPNETWORKDATAMODEL_H

#include <QByteArray>
#include <QVector>

class HPNetworkDataModel
{
public:

    enum HPDataType
    {
        HP_UNSIGNED_8 = 0,
        HP_SIGNED_8,
        HP_UNSIGNED_16,
        HP_SIGNED_16,
        HP_UNSIGNED_32,
        HP_SIGNED_32,
        HP_CHAR,
        HP_BOOL
    };

    HPNetworkDataModel();
    ~HPNetworkDataModel();

    void resetModel(void);
    void resetDataBox(void);

    void pushDataType(void);

    void pushData(void);

    void getDataBox(void);
    void getDataTypeList(void);

private:

    void initialize(void);

    QByteArray currentDataBox_;
    QVector<HPDataType> dataTypeList_;
};

#endif // HPNETWORKDATAPACKAGE_H
