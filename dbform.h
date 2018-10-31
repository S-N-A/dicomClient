#ifndef DBFORM_H
#define DBFORM_H

#include <QWidget>
#include <QBuffer>
#include <QSqlError>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlRecord>
#include <logger.h>
#include <tagshelpers.h>

namespace Ui {
class DbForm;
}

class DbForm : public QWidget
{
    Q_OBJECT

public:
    explicit DbForm(QWidget *parent = nullptr);
    dicomDict deserialize(const QString& data) const;
    QString serialize(const dicomDict& data) const;
    ~DbForm();

public slots:
    void acceptInsertSignal(QString& name, QImage& image, dicomDict& dict);

private:
    Ui::DbForm *ui;
    const QString m_dbPath;
    const QString m_dbTable;
    QSqlDatabase m_db;
    const QString m_tableName = "PATIENT";
    bool initTableWidget();
    bool dumpToDb(QString& name, QImage& image, dicomDict& dict);
};

#endif // DBFORM_H
