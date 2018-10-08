#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    QIcon viewerIcon(QString(":/icons/viewerIcon"));
    QIcon dbIcon(QString(":/icons/db"));
    QIcon accessibilityIcon(QString(":/icons/accessibility"));
    ui->sideBarWidget->addAction(QString("Просмотр"), viewerIcon);
    ui->sideBarWidget->addAction(QString("База данных"), dbIcon);
    ui->sideBarWidget->addAction(QString("Проверить доступность"), accessibilityIcon);
    scene = new QGraphicsScene();
}

MainWindow::~MainWindow()
{
    delete scene;
    delete ui;

}

void MainWindow::on_loadDicomButton_clicked()
{

    fileName = QFileDialog::getOpenFileName(this, tr("Open dicom file"), tr("/home/ilya/"), tr("*.dcm"));
    if (fileName.isEmpty()){
        QMessageBox::warning(this, tr("Error"), tr("Error reading file: %1").arg(fileName));
        return;
    }
    gdcm::ImageReader ir;
    ir.SetFileName(fileName.toStdString().c_str());
    if (!ir.Read()){
        QMessageBox::warning(this, tr("Error"), tr("Failed to parse file: %1").arg(fileName));
        return;
    }
    gdcm::DataSet ds;
    qDebug() << "Getting image from ImageReader object";
    const gdcm::Image &gImage = ir.GetImage();
    std::vector<char> vbuffer;
    vbuffer.resize(gImage.GetBufferLength()); //?
    char *buffer = &vbuffer[0];

    QImage *imageQt= nullptr;
    if (!ConvertToFormat_RGB888(gImage, buffer, imageQt)){
        QMessageBox::warning(this, tr("Error"), tr("Couldnt convert image to RGB 888"));
        return;
    }
    scene->clear();
    scene->addPixmap(QPixmap::fromImage(*imageQt));
    ui->dicomGraphicsView->setScene(scene);

}

/*
 * This function should be researched on purpose of colliding with another widgets in future
 */
void MainWindow::showEvent(QShowEvent*){
    ui->dicomGraphicsView->fitInView(scene->sceneRect(), Qt::AspectRatioMode::KeepAspectRatio);
}

// Should be removed
void MainWindow::on_pushButton_clicked()
{
    if(CEcho()){
        QMessageBox::warning(this, tr("C-ECHO"),tr("Получилось"));
    } else{
        QMessageBox::warning(this, tr("C-ECHO"), tr("Failed"));
    }
}
