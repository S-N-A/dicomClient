#ifndef SENDDIALOG_H
#define SENDDIALOG_H

#include <QDialog>
#include <QTcpSocket>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QIcon>
#include <QMessageBox>
#include  "logger.h"
#include "telemedobject.h"

namespace Ui {
class SendDialog;
}

namespace{
    const QString dbTable = "patient";
    const QString dbFile = "dicom.db";

}

class SendDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SendDialog(QWidget *parent = nullptr);
    ~SendDialog();

private slots:
    void on_pushButton_clicked();

private:
    QTcpSocket m_tcpSocket;
    QSqlDatabase m_db;
    Ui::SendDialog *ui;
    bool initTable();
    TeleMedObject buildTeleMedObject();
    void sendData(QByteArray& ba);
};

#endif // SENDDIALOG_H
