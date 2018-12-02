#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{    
    ui->setupUi(this);
    this->initSidebar();
    ui->viewerWidget->hide();
    ui->accessibilityWidget->hide();
    ui->dbWidget->hide();

}

void MainWindow::getData(QByteArray block){
    qDebug(logDebug())<< block;
}

void MainWindow::displayDbLayout(){
    ui->viewerWidget->hide();
    ui->accessibilityWidget->hide();
    ui->dbWidget->show();
    ui->dbWidget->setGeometry(m_standartXGeom, m_standartYGeom, m_standartWidth, m_standartHeight);
    ui->dbWidget->update();
}

void MainWindow::displayAccessibilityLayout(){
    ui->viewerWidget->hide();
    ui->dbWidget->hide();
    ui->accessibilityWidget->show();
    ui->accessibilityWidget->setGeometry(m_standartXGeom, m_standartYGeom, m_standartWidth, m_standartHeight);
    ui->accessibilityWidget->update();
}

void MainWindow::displayViewerLayout(){
    ui->accessibilityWidget->hide();
    ui->dbWidget->hide();
    ui->viewerWidget->show();
    ui->viewerWidget->setGeometry(m_standartXGeom, m_standartYGeom, m_standartWidth, m_standartHeight);
    ui->viewerWidget->update();
}



void MainWindow::initSidebar(){
    QIcon viewerIcon(QString(":/icons/viewerIcon"));
    QIcon dbIcon(QString(":/icons/db"));
    QIcon accessibilityIcon(QString(":/icons/accessibility"));
    QAction *viewerAction = new QAction(viewerIcon, QString("Просмотр"));
    QAction *dbAction = new QAction(dbIcon, QString("База данных"));
    QAction *checkAction = new QAction(accessibilityIcon, QString("Сетевое взаимодействие"));
    connect(viewerAction, SIGNAL(triggered()), this, SLOT(displayViewerLayout()));
    connect(dbAction, SIGNAL(triggered()), this, SLOT(displayDbLayout()));
    connect(checkAction, SIGNAL(triggered()), this, SLOT(displayAccessibilityLayout()));
    connect(ui->viewerWidget, SIGNAL(sendInsertSignal(QString&, QImage&, dicomDict&, addInfoMap&)), ui->dbWidget,
            SLOT(acceptInsertSignal(QString&, QImage&, dicomDict&, addInfoMap&)));
    connect(ui->accessibilityWidget, SIGNAL(sendSignalToDump(QString& name, QImage& image, dicomDict& dict, addInfoMap& map)),
                                            ui->dbWidget,
            SLOT(acceptInsertSignal(QString& name, QImage& image, dicomDict& dict, addInfoMap& map)));
    ui->sideBarWidget->addAction(viewerAction);
    ui->sideBarWidget->addAction(dbAction);
    ui->sideBarWidget->addAction(checkAction);
}




MainWindow::~MainWindow()
{

    delete ui;

}
