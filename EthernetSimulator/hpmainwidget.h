#ifndef HPMAINWIDGET_H
#define HPMAINWIDGET_H

#include <QLabel>
class QLineEdit;
class QComboBox;
class QPushButton;
class QTabWidget;

#include <QWidget>

class HPMainWidget : public QWidget
{
    Q_OBJECT

public:
    HPMainWidget(QWidget *parent = nullptr);
    ~HPMainWidget();

    void initialize(void);
    void showScreen(void);

private:

    QLabel * addressLabel_p;
    QLineEdit * addressLEdit_p;
    QLabel * portLabel_p;
    QLineEdit * portLEdit_p;
    QComboBox * connectionTypeComboBox_p;
    QLabel * refreshLabel_p;
    QLineEdit * refreshLEdit_p;
    QLabel * connectionTypeLabel_p;
    QPushButton * connectButton_p;
    QPushButton * importButton_p;
    QPushButton * exportButton_p;
    QTabWidget * dataViewTabWidget_p;


};
#endif // HPMAINWIDGET_H
