#ifndef HPXMLOPERATOR_H
#define HPXMLOPERATOR_H

#include <QString>

class HPXmlOperator
{
public:
    HPXmlOperator();

    ~HPXmlOperator();

    void importConfigurationFile(const QString& fileName);
    void exportConfigurationFile(const QString& fileName);

private:

    void initialize(void);

};

#endif // HPXMLOPERATOR_H
