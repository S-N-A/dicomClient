#ifndef VIEWERFORM_H
#define VIEWERFORM_H

#include <QWidget>
#include <QString>
#include <QShowEvent>
#include <QGraphicsScene>
#include <QFileDialog>
#include <QMessageBox>
#include <converters.h>
#include <QDebug>

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
    void getTags(gdcm::DataSet&) const;
    explicit ViewerForm(QWidget *parent = nullptr);
    ~ViewerForm();

private slots:
    void on_loadImageButton_clicked();


private:
    Ui::ViewerForm *ui;
};

#endif // VIEWERFORM_H
