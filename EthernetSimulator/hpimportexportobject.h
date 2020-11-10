#ifndef HPIMPORTEXPORTOBJECT_H
#define HPIMPORTEXPORTOBJECT_H

class HPCsvOperator;
class HPXmlOperator;

#include <QObject>
#include <QString>
#include <QVector>
#include <QStringList>

class HPImportExportObject : public QObject
{
    Q_OBJECT
public:
    explicit HPImportExportObject(QObject *parent = nullptr);
    virtual ~HPImportExportObject();

    bool importConfigurationFile(const QString& fileName);
    bool exportConfigurationFile(const QString& fileName);

    QVector<QStringList> getDefinedStringList(void);

private:

    void initialize(void);

    HPCsvOperator * csvOperator_p;
    HPXmlOperator * xmlOperator_p;

signals:

};

#endif // HPIMPORTEXPORTOBJECT_H
