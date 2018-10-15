#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{    
    ui->setupUi(this);
    this->initSidebar();
    ui->viewerWidget->hide();
}

void MainWindow::displayDbLayout(){

}

void MainWindow::displayAccessibilityLayout(){

}

void MainWindow::displayViewerLayout(){
    ui->viewerWidget->show();
    ui->viewerWidget->setGeometry(150, 24, 1051, 975);
    ui->viewerWidget->update();
}


void MainWindow::initSidebar(){
    QIcon viewerIcon(QString(":/icons/viewerIcon"));
    QIcon dbIcon(QString(":/icons/db"));
    QIcon accessibilityIcon(QString(":/icons/accessibility"));
    QAction *viewerAction = new QAction(viewerIcon, QString("Просмотр"));
    QAction *dbAction = new QAction(dbIcon, QString("База данных"));
    QAction *checkAction = new QAction(accessibilityIcon, QString("Проверить доступность"));
    connect(viewerAction, SIGNAL(triggered()), this, SLOT(displayViewerLayout()));
    connect(dbAction, SIGNAL(triggered()), this, SLOT(displayDbLayout()));
    connect(checkAction, SIGNAL(triggered()), this, SLOT(displayAccessibilityLayout()));
    ui->sideBarWidget->addAction(viewerAction);
    ui->sideBarWidget->addAction(dbAction);
    ui->sideBarWidget->addAction(checkAction);
}




MainWindow::~MainWindow()
{

    delete ui;

}
