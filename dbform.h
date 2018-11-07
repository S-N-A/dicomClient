#ifndef DBFORM_H
#define DBFORM_H

#include <QWidget>
#include <QGraphicsScene>
#include <QTableWidgetItem>
#include <QBuffer>
#include <QSqlError>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlRecord>
#include <logger.h>
#include <tagshelpers.h>
#include <serializehelper.h>

namespace Ui {
class DbForm;
}

class DbForm : public QWidget
{
    Q_OBJECT

public:
    explicit DbForm(QWidget *parent = nullptr);
    ~DbForm();

public slots:
    void acceptInsertSignal(QString& name, QImage& image, dicomDict& dict);

private slots:
    void on_dbTableWidget_cellClicked(int row, int column);

private:
    Ui::DbForm *ui;
    enum class columns {id = 0, name = 1, image = 2, data = 3};
    enum dicomColumns{tag, description, value};
    bool askForSave();
    void previewImage(const int& id);
    const QString m_dbPath;
    const QString m_dbTable;
    const QIcon m_okIcon;
    const QIcon m_unavailableIcon;
    QSqlDatabase m_db;
    QGraphicsScene m_previewScene;
    bool initTableWidget();
    bool dumpToDb(QString& name, QImage& image, dicomDict& dict);
    void initBorderWidget(const dicomDict &dict);
};

#endif // DBFORM_H
