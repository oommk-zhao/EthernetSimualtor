#ifndef HPIMPORTEXPORTOBJECT_H
#define HPIMPORTEXPORTOBJECT_H

#include <QObject>

class HPImportExportObject : public QObject
{
    Q_OBJECT
public:
    explicit HPImportExportObject(QObject *parent = nullptr);

signals:

};

#endif // HPIMPORTEXPORTOBJECT_H
