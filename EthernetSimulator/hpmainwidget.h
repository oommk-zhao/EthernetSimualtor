#ifndef HPMAINWIDGET_H
#define HPMAINWIDGET_H

#include <QLabel>
#include <QStringList>
#include <QVector>
#include <QByteArray>
#include <QWidget>

class QLineEdit;
class QComboBox;
class QPushButton;
class QTabWidget;
class QTimer;
class QWidget;


/* First version, we only support TCP Server with sending value function, and will show the received raw data. */

class HPMainWidget : public QWidget
{
    Q_OBJECT

public:
    HPMainWidget(QWidget *parent = nullptr);
    ~HPMainWidget();

    void initialize(void);
    void showScreen(void);

    void initializeRawDataWidget(void);

    void initializeLocalDataWidget(const QVector<QStringList>& initializedList);
    void updateWidget(const QStringList& dataList);
    void pushRawData(const QByteArray& byteArrayData);
    QVector<QStringList> getDataList(void);

    QString getIPAddress(void) const;
    QString getPort(void) const;
    QString getConnectionType(void) const;
    int getRefreshTime(void) const;

signals:

    void singalRequestImport(QString);
    void signalRequestConnect(void);

private slots:

    void slotImportReleaed(void);

private:

    const int nameIndex_;
    const int valueIndex_;
    const int defaultValueIndex_;

    const int nameLabelWidth_;
    const int nameLabelHeight_;
    const int valueLabelWidth_;
    const int valueLabelHeight_;
    const int nameValueBlockWidth_;

    const int defaultRawLabelCount_;

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

    QWidget * localDataWidget_p;
    QWidget * rawDataWidget_p;
    QVector<QWidget *> connectedSocketWidget_p;

    QVector<QString> localNameLabelList_;
    QVector<QLineEdit *> localValueEditList_;
    QVector<QLabel *> rawDataLabelList_;



};
#endif // HPMAINWIDGET_H
