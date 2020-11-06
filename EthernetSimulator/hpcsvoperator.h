#ifndef HPCSVOPERATOR_H
#define HPCSVOPERATOR_H

#include <QString>

class HPCsvOperator
{
public:

    HPCsvOperator();
    ~HPCsvOperator();

    void importConfigurationFile(const QString& fileName);
    void exportConfigurationFile(const QString& fileName);

private:

    void initialize(void);

    const QString splitString_;

};

#endif // HPCSVOPERATOR_H
