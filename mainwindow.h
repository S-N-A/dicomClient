#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>
#include <QPixmap>
#include <QGraphicsScene>
#include <QImageWriter>
#include <QShowEvent>
#include <QMessageBox>
#include "gdcmImageReader.h"
#include "gdcmScanner.h"
#include "gdcmGlobal.h"
#include "gdcmDicts.h"
#include "gdcmDict.h"
#include "gdcmAttribute.h"
#include "gdcmStringFilter.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QString fileName;
    QGraphicsScene *scene;
    void showEvent(QShowEvent*);
    bool ConvertToFormat_RGB888(gdcm::Image const & gimage, char *buffer, QImage* &imageQt);
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_loadDicomButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
