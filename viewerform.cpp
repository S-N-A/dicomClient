#include "viewerform.h"
#include "ui_viewerform.h"

ViewerForm::ViewerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewerForm)
{
    ui->setupUi(this);
    scene = new QGraphicsScene();
}

ViewerForm::~ViewerForm()
{
    delete scene;
    delete ui;
}

void ViewerForm::on_loadImageButton_clicked()
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

void ViewerForm::showEvent(QShowEvent*){
    ui->dicomGraphicsView->fitInView(scene->sceneRect(), Qt::AspectRatioMode::KeepAspectRatio);
}


void ViewerForm::getTags(gdcm::DataSet&) const{
    const gdcm::Global& g = gdcm::Global::GetInstance();
    const gdcm::Dicts &dicts = g.GetDicts();
    const gdcm::Dict &pubdict = dicts.GetPublicDict();
    gdcm::Tag tPatientsName;
      //const DictEntry &de2 =
    pubdict.GetDictEntryByName("Patient's Name", tPatientsName);
    QString(tPatientsName.IsIllegal())
}
