#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QIcon>

#include <viewerform.h>
#include <converters.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QString fileName;
    void initSidebar();
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void displayViewerLayout();
    void displayDbLayout();
    void displayAccessibilityLayout();


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
