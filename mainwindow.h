#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <QPixmap>
#include <QGraphicsScene>
#include <QImageWriter>
#include <QShowEvent>
#include <QMessageBox>
#include <QIcon>


#include <converters.h>

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
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_loadDicomButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
