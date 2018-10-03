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
    // PrintCSA(fileName.toStdString());
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

//bool MainWindow::ConvertToFormat_RGB888(gdcm::Image const & gimage, char *buffer, QImage* &imageQt){
//    const unsigned int* dimension = gimage.GetDimensions();

//    unsigned int dimX = dimension[0];
//    unsigned int dimY = dimension[1];

//    gimage.GetBuffer(buffer);

//    // Let's start with the easy case:
//    if( gimage.GetPhotometricInterpretation() == gdcm::PhotometricInterpretation::RGB )
//      {
//      if( gimage.GetPixelFormat() != gdcm::PixelFormat::UINT8 )
//        {
//        return false;
//        }
//      unsigned char *ubuffer = reinterpret_cast<unsigned char*>(buffer);
//      // QImage::Format_RGB888  13  The image is stored using a 24-bit RGB format (8-8-8).
//      imageQt = new QImage(reinterpret_cast<unsigned char*>(ubuffer), static_cast<int>(dimX), static_cast<int>(dimY),
//                           static_cast<int>(3*dimX), QImage::Format_RGB888);
//      }
//    else if( gimage.GetPhotometricInterpretation() == gdcm::PhotometricInterpretation::MONOCHROME2 )
//      {
//      if( gimage.GetPixelFormat() == gdcm::PixelFormat::UINT8 )
//        {
//        // We need to copy each individual 8bits into R / G and B:
//        unsigned char *ubuffer = new unsigned char[dimX*dimY*3];
//        unsigned char *pubuffer = ubuffer;
//        for(unsigned int i = 0; i < dimX*dimY; i++)
//          {
//          *pubuffer++ = *buffer;
//          *pubuffer++ = *buffer;
//          *pubuffer++ = *buffer++;
//          }

//        imageQt = new QImage(ubuffer, static_cast<int>(dimX), static_cast<int>(dimY), QImage::Format_RGB888);
//        }
//      else if( gimage.GetPixelFormat() == gdcm::PixelFormat::INT16 )
//        {
//        // We need to copy each individual 16bits into R / G and B (truncate value)
//        short *buffer16 = reinterpret_cast<short*>(buffer);
//        unsigned char *ubuffer = new unsigned char[dimX*dimY*3];
//        unsigned char *pubuffer = ubuffer;
//        for(unsigned int i = 0; i < dimX*dimY; i++)
//          {
//          // Scalar Range of gdcmData/012345.002.050.dcm is [0,192], we could simply do:
//          // *pubuffer++ = *buffer16;
//          // *pubuffer++ = *buffer16;
//          // *pubuffer++ = *buffer16;
//          // instead do it right:
//          *pubuffer++ = static_cast<unsigned char>(std::min(255, (32768 + *buffer16) / 255));
//          *pubuffer++ = static_cast<unsigned char>(std::min(255, (32768 + *buffer16) / 255));
//          *pubuffer++ = static_cast<unsigned char>(std::min(255, (32768 + *buffer16) / 255));
//          buffer16++;
//          }

//        imageQt = new QImage(ubuffer, static_cast<int>(dimX), static_cast<int>(dimY), QImage::Format_RGB888);
//        }
//      else
//        {
//        std::cerr << "Pixel Format is: " << gimage.GetPixelFormat() << std::endl;
//        return false;
//        }
//      }
//    else
//      {
//      std::cerr << "Unhandled PhotometricInterpretation: " << gimage.GetPhotometricInterpretation() << std::endl;
//      return false;
//      }

//    return true;

//}

void MainWindow::on_pushButton_clicked()
{
    if(CEcho()){
        QMessageBox::warning(this, tr("C-ECHO"),tr("Получилось"));
    } else{
        QMessageBox::warning(this, tr("C-ECHO"), tr("Failed"));
    }
}
