#ifndef VIEWERFORM_H
#define VIEWERFORM_H

#include <QWidget>
#include <QString>
#include <QCheckBox>
#include <QShowEvent>
#include <QMap>
#include <QGraphicsScene>
#include <QFileDialog>
#include <QMessageBox>
#include <converters.h>
#include <tagshelpers.h>
#include <QDebug>
#include <logger.h>
#include "telemedobject.h"

namespace Ui {
class ViewerForm;
}

class ViewerForm : public QWidget
{
    Q_OBJECT

public:
    QString fileName;
    QGraphicsScene *scene;
    void showEvent(QShowEvent*);
    explicit ViewerForm(QWidget *parent = nullptr);
    ~ViewerForm();

private slots:
    void on_loadImageButton_clicked();

    void on_dicomAttributeTableWidget_cellChanged(int row, int column);

signals:
    void sendInsertSignal(QString& name, QImage& image, dicomDict& dict);

private:
    bool showMessageBoxAskingForChange();
    bool m_changeAllowed;
    enum m_columns{Tag, Description, Value};
    const int m_table_columns_count = 3;
    void initTable(const dicomDict& dict); // Should be refactored with dbform;
    Ui::ViewerForm *ui;
};

#endif // VIEWERFORM_H
