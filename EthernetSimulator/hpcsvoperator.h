#ifndef HPCSVOPERATOR_H
#define HPCSVOPERATOR_H

#include <QSet>
#include <QVector>
#include <QString>
#include <QStringList>

class HPCsvOperator
{
public:

    HPCsvOperator();
    ~HPCsvOperator();

    int importConfigurationFile(const QString& fileName);
    void exportConfigurationFile(const QString& fileName);

    QStringList getTypeStringList(void);
    QVector<QStringList> getDefinedStringList(void);

private:

    void initialize(void);

    bool checkFileLegality(const QStringList& fileHeadAndEnd);
    bool importData(const QString& csvHead, const QStringList& importData);

    const QString splitString_;
    const QString fileCode_;
    const int typeIndex_;
    const QString charDefinedStr_;
    const int charSizeIndex_;

    /* No used in first version, we temporary use pre-defined (hardcode) columns in Import */
    QStringList typeStringList_;

    QVector<QStringList> definedStringList_;

    QSet<QString> availableTypeList_;
    QStringList availableHeadList_;

};

#endif // HPCSVOPERATOR_H
