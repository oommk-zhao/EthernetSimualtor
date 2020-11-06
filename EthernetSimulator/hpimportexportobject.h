#ifndef HPIMPORTEXPORTOBJECT_H
#define HPIMPORTEXPORTOBJECT_H

class HPCsvOperator;
class HPXmlOperator;

#include <QObject>
#include <QString>

class HPImportExportObject : public QObject
{
    Q_OBJECT
public:
    explicit HPImportExportObject(QObject *parent = nullptr);
    virtual ~HPImportExportObject();

    void importConfigurationFile(const QString& fileName);
    void exportConfigurationFile(const QString& fileName);

private:

    void initialize(void);

    HPCsvOperator * csvOperator_p;
    HPXmlOperator * xmlOperator_p;

signals:

};

#endif // HPIMPORTEXPORTOBJECT_H
