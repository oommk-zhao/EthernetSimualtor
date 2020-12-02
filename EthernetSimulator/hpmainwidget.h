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
class QGroupBox;


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
    void initializeChecksumWidget(void);

    void initializeLocalDataWidget(const QVector<QStringList>& initializedList);
    void updateWidget(const QStringList& dataList);
    void pushRawData(const QByteArray& byteArrayData);
    QVector<QStringList> getDataList(void);

    QString getIPAddress(void) const;
    QString getPort(void) const;
    QString getConnectionType(void) const;
    int getRefreshTime(void) const;
    bool checkTheValidity(const QByteArray& rawArrayData);
    void extractValues(const QByteArray& rawArrayData);

signals:

    void singalRequestImport(QString);
    void signalRequestConnect(void);
    void signalRequestCheckValidity(void);

private slots:

    void slotImportReleaed(void);

private:

    uint16_t crc16_ccitt(const QByteArray& puchMsg);
    QByteArray changeToAustraliaSCGTLoco(uint16_t inputValue);

    const int nameIndex_;
    const int valueIndex_;
    const int defaultValueIndex_;

    const int nameLabelWidth_;
    const int nameLabelHeight_;
    const int valueLabelWidth_;
    const int valueLabelHeight_;
    const int nameValueBlockWidth_;

    const int defaultRawLabelCount_;

    /* Main Widget */
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

    /* Checksum Widget */
    QLabel * projectNameLabel_p;
    QComboBox * projectNameCombo_p;
    QPushButton * checkButton_p;
    QGroupBox * resultGroupWidget_p;
    QLabel * usedChecksumNameLabel_p;
    QLabel * checkedBytesLabel_p;
    QLabel * calculatedCrcNameLabel_p;
    QLabel * calculatedCrcLabel_p;
    QLabel * expectedCrcNameLabel_p;
    QLabel * expectedCrcResultLabel_p;
    QLabel * extractedCrcNameLabel_p;
    QLabel * extractedCrcResultLabel_p;

    QLabel * extractedCountNameLabel_p;
    QLabel * extractedCountResultLabel_p;
    QLabel * extractedLongitudeNameLabel_p;
    QLabel * extractedLongitudeResultLabel_p;
    QLabel * extractedLatitudeNameLabel_p;
    QLabel * extractedLatitudeResultLabel_p;
    QLabel * extractedAltitudeNameLabel_p;
    QLabel * extractedAltitudeResultLabel_p;
    QLabel * extractedDateNameLabel_p;
    QLabel * extractedDateResultLabel_p;
    QLabel * extractedTimeNameLabel_p;
    QLabel * extractedTimeResultLabel_p;

    QWidget * localDataWidget_p;
    QWidget * rawDataWidget_p;
    QWidget * validityWidget_p;
    QVector<QWidget *> connectedSocketWidget_p;

    QVector<QString> localNameLabelList_;
    QVector<QLineEdit *> localValueEditList_;
    QVector<QLabel *> rawDataLabelList_;



};
#endif // HPMAINWIDGET_H
