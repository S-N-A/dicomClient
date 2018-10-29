#ifndef DBFORM_H
#define DBFORM_H

#include <QWidget>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlRecord>
#include <logger.h>


namespace Ui {
class DbForm;
}

class DbForm : public QWidget
{
    Q_OBJECT

public:
    explicit DbForm(QWidget *parent = nullptr);
    ~DbForm();

private:
    Ui::DbForm *ui;
    const QString m_dbPath;
    QSqlDatabase m_db;
    const QString m_tableName = "PATIENT";
    bool initTableWidget();
};

#endif // DBFORM_H
