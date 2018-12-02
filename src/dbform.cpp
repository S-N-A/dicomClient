#include "dbform.h"
#include "ui_dbform.h"

DbForm::DbForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DbForm), m_dbPath("dicom.db"), m_dbTable("patient"),
    m_okIcon(":/icons/ok"),m_unavailableIcon(":/icons/unavailable"), m_updateIcon(":/icons/update")
{
    ui->setupUi(this);
    ui->updateButton->setIcon(m_updateIcon);
    ui->updateButton->setIconSize(QSize(21,25));
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(m_dbPath);
    if (!m_db.open()){
        qCritical(logCritical()) << "Couldn't open connection to database " << m_dbPath;
        QMessageBox::warning(this, tr("Ошибка"), tr("Ошибка доступа к базе данных"));
    }
    qDebug(logDebug()) << m_db.connectOptions();
    initTableWidget();
    m_previewScene.clear();

}


bool DbForm::initTableWidget(){
    QSqlQuery query;
    QStringList headers;
    /*
    Bind value didn't work, so hard code for now
    */
    query.prepare("SELECT * FROM " + m_dbTable);
    if(!query.exec()){
            qDebug(logCritical()) << "Critical DB error - Couldn't exec last query";
    }

    qDebug(logDebug()) << query.lastQuery();
    ui->dbTableWidget->setColumnCount(query.record().count());
    ui->dbTableWidget->setRowCount(100); // No support for size() in sqlite
    qDebug(logDebug()) << "Query record count - " << query.record().count();
    ui->dbTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    for(int index=0; index< query.record().count(); index++){
        headers << query.record().fieldName(index);
    }

    ui->dbTableWidget->setHorizontalHeaderLabels(headers);
    for (int counter = 0; query.next(); counter++){
        QTableWidgetItem *id = new QTableWidgetItem(query.value(0).toString());
        QTableWidgetItem *name = new QTableWidgetItem(query.value(1).toString());
        ui->dbTableWidget->setItem(counter, static_cast<int>(columns::id), id);
        id->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        ui->dbTableWidget->setItem(counter, static_cast<int>(columns::name), name);
        name->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        if (query.value(static_cast<int>(columns::image)).isNull()){
            QTableWidgetItem *null = new QTableWidgetItem();
            null->setIcon(m_unavailableIcon);
            null->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
            ui->dbTableWidget->setItem(counter, static_cast<int>(columns::image), null);
        } else {
            QTableWidgetItem *exist = new QTableWidgetItem();
            exist->setIcon(m_okIcon);
            exist->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
            ui->dbTableWidget->setItem(counter, static_cast<int>(columns::image), exist);
        }
        if (query.value(static_cast<int>(columns::data)).isNull()){
            QTableWidgetItem *null = new QTableWidgetItem();
            null->setIcon(m_unavailableIcon);
            null->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
            ui->dbTableWidget->setItem(counter, static_cast<int>(columns::data), null);
        } else {
            QTableWidgetItem *exist = new QTableWidgetItem();
            exist->setIcon(m_okIcon);
            exist->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
            ui->dbTableWidget->setItem(counter, static_cast<int>(columns::data), exist);
        }
       QTableWidgetItem* request = new QTableWidgetItem(query.value(4).toString());
       ui->dbTableWidget->setItem(counter, 4, request);
       QTableWidgetItem* response = new QTableWidgetItem(query.value(5).toString());
       ui->dbTableWidget->setItem(counter, 5, response);
       QTableWidgetItem* request_date = new QTableWidgetItem(query.value(6).toString());
       ui->dbTableWidget->setItem(counter, 6, request_date);
       QTableWidgetItem* response_date = new QTableWidgetItem(query.value(7).toString());
       ui->dbTableWidget->setItem(counter, 7, response_date);
       QTableWidgetItem* requester = new QTableWidgetItem(query.value(8).toString());
       ui->dbTableWidget->setItem(counter, 8, requester);
       QTableWidgetItem* responser = new QTableWidgetItem(query.value(9).toString());
       ui->dbTableWidget->setItem(counter, 9, responser);

    }
    return true;
}

void DbForm::previewImage(const int& id){
    QSqlQuery query;
    QByteArray ba;
    query.prepare("SELECT image FROM " + m_dbTable + " WHERE id=" + QString::number(id));
    if ( !query.exec()){
        // Fail silently for now
        qDebug(logCritical()) << "Couldn't execute following query" << query.lastQuery();
        return;
    }
    query.first();
    ba = query.value(0).toByteArray();
    if ( ba.isEmpty()){
        qDebug(logCritical()) << "Image in db is empty or query is broken";
        return;
    }
    QImage img = Serialize::byteArrayToImage(ba);
    m_previewScene.clear();
    m_previewScene.addPixmap(QPixmap::fromImage(img));
    ui->dbGraphicsView->setScene(&m_previewScene);
    ui->dbGraphicsView->fitInView(m_previewScene.sceneRect(),
                                  Qt::KeepAspectRatio);
    ui->dbGraphicsView->update();
}

bool DbForm::dumpToDb(QString& name, QImage& image, dicomDict& dict, addInfoMap& map){
    QSqlQuery query;

    // Dump image in bytearray
    QByteArray imageByteArray = Serialize::imageToByteArray(image);

    // Dump dict in bytearray
    QByteArray dataByteArray = Serialize::dictToByteArray<dicomDict>(dict);

    query.prepare("INSERT INTO patient(name, image, data) VALUES (:name, :image, :data)");
    query.bindValue(":name", name);
    query.bindValue(":image", imageByteArray);
    query.bindValue(":data", dataByteArray);
    if (!query.exec()){
        qDebug(logCritical()) << "Couldn't insert object in DB " << query.lastError();
        qDebug(logCritical()) << query.lastQuery();
        QMessageBox::warning(this, "Ошибка", "Запись в базу была завершена с ошибкой");
        return false;
    }
    insertAdditionalInfo(query, map);
    initTableWidget();
    return true;
}

void DbForm::insertAdditionalInfo(QSqlQuery& query, const addInfoMap& map){
    if(!map.isEmpty()){
        auto request = map.value("request");
        auto response = map.value("response");
        auto request_date = map.value("request_date");
        auto response_date = map.value("response_date");
        auto requester = map.value("requester");
        auto responser = map.value("responser");

        query.prepare("INSERT INTO patient (request, response, request_date, response_date, requester, responser)"
                      "VALUES (:request, :response, :request_date, :response_date, :requester, :responser)");
        query.bindValue(":request", request);
        query.bindValue(":response", response);
        query.bindValue(":request_date", request_date);
        query.bindValue(":response_date", response_date);
        query.bindValue(":requester", requester);
        query.bindValue(":responser", responser);
        if (!query.exec()){
            qDebug(logCritical()) << "Couldn't insert object in DB " << query.lastError();
            qDebug(logCritical()) << query.lastQuery();
            QMessageBox::warning(this, "Ошибка", "Запись в базу была завершена с ошибкой");
            return;
        }

    }
}


bool DbForm::askForSave(){
    QMessageBox box;
    box.setText("Сохранение в базу");
    box.setInformativeText("Был загружен новый файл. Сохранить в локальную базу?");
    box.setWindowTitle("Сохранение");
    box.setIcon(QMessageBox::Question);

    box.setStandardButtons(QMessageBox::Discard | QMessageBox::Ok);
    box.setDefaultButton(QMessageBox::Ok);
    int ret = box.exec();
    switch(ret){
    case QMessageBox::Ok:
        return true;
    case QMessageBox::Discard:
        return false;
    default:
        return false;
    }
}

void DbForm::acceptInsertSignal(QString& name, QImage& image, dicomDict& dict, addInfoMap& map){
    qDebug(logDebug()) << "Signal accepted by db form";
    if(askForSave()){
        dumpToDb(name, image, dict, map);
    } else {
        return;
    }

}

DbForm::~DbForm()
{
    delete ui;
}



void DbForm::on_dbTableWidget_cellClicked(int row, int column)
{
    QSqlQuery query;
    QTableWidgetItem* idItem{ui->dbTableWidget->item(row, static_cast<int>(columns::id))};
    QByteArray dataByteArray;
    dicomDict dict;
    if(!idItem){
        return;
    }
    previewImage(idItem->text().toInt());
    query.prepare("SELECT data FROM " + m_dbTable + " WHERE id=" + idItem->text());
//    query.bindValue(":id", idItem->text());
    if ( !query.exec() ){
        qDebug(logCritical()) << "Critical DB error - Couldn't exec last query";
        return;
    }
    qDebug(logDebug()) << query.lastQuery();
    query.first();
    dataByteArray = query.value(0).toByteArray();
    // Check if no data on element
    if (dataByteArray.isEmpty()){
        return;
    }
    dict = Serialize::byteArrayToDict<dicomDict>(&dataByteArray);
    qDebug(logDebug()) << "Query record count: " << query.record().count();
    initFooterTable(ui->dbBorderDicomTable, dict);

    return;
}

void DbForm::initFooterTable(QTableWidget* widget, const dicomDict& dict){
    widget->clear();
    widget->setColumnCount(3);
    widget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    widget->setHorizontalHeaderLabels(QStringList() << "Tag" << "Description" << "Value");
    widget->setRowCount(dict.size());
    widget->blockSignals(true);
    int i =0;
    for(auto key: dict.keys()){
        QTableWidgetItem* tagItem = new QTableWidgetItem(key.toStdString().c_str());
        QTableWidgetItem* descriptionItem = new QTableWidgetItem(dict[key].first.toStdString().c_str());
        QTableWidgetItem* valueItem = new QTableWidgetItem(dict[key].second.toStdString().c_str());
        widget->setItem(i, dicomColumns::tag, tagItem);
        tagItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        widget->setItem(i, dicomColumns::description, descriptionItem);
        descriptionItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        widget->setItem(i, dicomColumns::value, valueItem);
        valueItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        i++;
    }
    widget->blockSignals(false);
    widget->update();
    return;
}



void DbForm::on_updateButton_clicked()
{
    initTableWidget();
}
