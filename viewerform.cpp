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
    dicomDict map = getTags(fileName.toStdString().c_str());
    // To delete. For debug purposes
    dicomDict::Iterator it;
    for (it=map.begin(); it!=map.end(); ++it){
        qDebug() << it.key().c_str() << it.value().first.c_str() << it.value().second.c_str();
    }

    initTable(map); // fill table with dicom attributes

    // output image
    scene->clear();
    scene->addPixmap(QPixmap::fromImage(*imageQt));
    ui->dicomGraphicsView->setScene(scene);
}

void ViewerForm::showEvent(QShowEvent*){
    ui->dicomGraphicsView->fitInView(scene->sceneRect(), Qt::AspectRatioMode::KeepAspectRatio);
}


void ViewerForm::initTable(const dicomDict& dict){
    ui->dicomAttributeTableWidget->setColumnCount(m_table_columns_count);
    ui->dicomAttributeTableWidget->setRowCount(dict.size());
    ui->dicomAttributeTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->dicomAttributeTableWidget->setHorizontalHeaderLabels(QStringList() << "Tag" << "Description" << "Value");
    int i = 0; // TODO: Dirty unneeded assignment
    ui->dicomAttributeTableWidget->blockSignals(true);
    for(auto key: dict.keys()){
        QTableWidgetItem* tagItem = new QTableWidgetItem(tr(key.c_str()));
        QTableWidgetItem* descriptionItem = new QTableWidgetItem(dict[key].first.c_str());
        QTableWidgetItem* valueItem = new QTableWidgetItem(dict[key].second.c_str());
        ui->dicomAttributeTableWidget->setItem(i, m_columns::Tag, tagItem);
        tagItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        ui->dicomAttributeTableWidget->setItem(i, m_columns::Description, descriptionItem);
        descriptionItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        ui->dicomAttributeTableWidget->setItem(i, m_columns::Value, valueItem);
        i++;
    }
    ui->dicomAttributeTableWidget->blockSignals(false);
    i=0;
    ui->dicomAttributeTableWidget->update();
    return;

}


void ViewerForm::on_dicomAttributeTableWidget_cellChanged(int row, int column)
{
    QTableWidgetItem* tag = ui->dicomAttributeTableWidget->item(row, m_columns::Tag);
    std::string tagAsString = tag->text().toStdString();

    QTableWidgetItem* value = ui->dicomAttributeTableWidget->item(row, column);
    std::string valueAsString = value->text().toStdString();
    if (!setTag(tagAsString, valueAsString, fileName.toStdString().c_str())){
        QMessageBox::warning(this, tr("Error"), tr("Error reading/writing file: %1").arg(fileName));
        return;
    }
    return;
}
