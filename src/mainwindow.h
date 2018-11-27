#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QIcon>
#include <QMessageBox>


#include <viewerform.h>
#include <converters.h>

namespace Ui {
class MainWindow;
}

using addInfoMap = QMap<QString, QString>;

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
    void getData(QByteArray block);

private:
    const int m_standartXGeom = 300;
    const int m_standartYGeom = 24;
    const int m_standartWidth = 1051;
    const int m_standartHeight = 975;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
