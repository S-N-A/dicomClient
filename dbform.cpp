#include "dbform.h"
#include "ui_dbform.h"

DbForm::DbForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DbForm), m_dbPath("dicom.db"), m_dbTable("patient")
{
    ui->setupUi(this);
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(m_dbPath);
    if (!m_db.open()){
        qCritical(logCritical()) << "Couldn't open connection to database " << m_dbPath;
        QMessageBox::warning(this, tr("Ошибка"), tr("Ошибка доступа к базе данных"));
    }
    qDebug(logDebug()) << m_db.connectOptions();

    initTableWidget();

}


bool DbForm::initTableWidget(){
    QSqlQuery query;
    query.prepare(tr("SELECT * FROM %1").arg(m_dbTable)); //TODO
    if(!query.exec()){
            qDebug(logCritical()) << "Critical DB error";
            throw QString("Coldn't select all data from database");
    }
    qDebug(logDebug()) << query.lastQuery();
    ui->dbTableWidget->setColumnCount(query.record().count());
    ui->dbTableWidget->setRowCount(100);
    qDebug(logDebug()) << "Query record count - " << query.record().count();
    ui->dbTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QStringList headers;
    for(int index=0; index< query.record().count(); index++){
        headers << query.record().fieldName(index);
    }
    ui->dbTableWidget->setHorizontalHeaderLabels(headers);
    for (int counter = 0; query.next(); counter++){
        QTableWidgetItem *id = new QTableWidgetItem(query.value(0).toString());
        QTableWidgetItem *name = new QTableWidgetItem(query.value(1).toString());
        ui->dbTableWidget->setItem(counter, 0, id);
        ui->dbTableWidget->setItem(counter, 1, name);
        if (query.value(2).isNull()){
            QTableWidgetItem *null = new QTableWidgetItem("Doesn't exist");
            ui->dbTableWidget->setItem(counter, 2, null);
        } else {
            QTableWidgetItem *exist = new QTableWidgetItem("Is present");
            ui->dbTableWidget->setItem(counter, 2, exist);
        }
        if (query.value(3).isNull()){
            QTableWidgetItem *null = new QTableWidgetItem("Doesn't exist");
            ui->dbTableWidget->setItem(counter, 3, null);
        } else {
            QTableWidgetItem *exist = new QTableWidgetItem("Is present");
            ui->dbTableWidget->setItem(counter, 3, exist);
        }

    }
    return true;
}



bool DbForm::dumpToDb(QString& name, QImage& image, dicomDict& dict){
    QSqlQuery query;
    // dump image first
    QByteArray inByteArray;
    QBuffer buffer(&inByteArray);
    buffer.open(QIODevice::WriteOnly);
    QPixmap pixmap(QPixmap::fromImage(image));
    pixmap.save(&buffer, "PNG");
    // Serialize map<string, pair<string, string> >
    // QString data = serialize(dict);


   // qDebug(logDebug()) << "Serialized dicom data" << data;
    query.prepare("INSERT INTO patient(name) VALUES (\"test_test\")");
    query.bindValue(":NAME", dict.begin().value().first.toStdString().c_str());
    if (!query.exec()){
        qDebug(logCritical()) << "Couldn't insert object in DB " << query.lastError();
        qDebug(logCritical()) << query.lastQuery();
        QMessageBox::warning(this, "Ошибка", "Запись в базу была завершена с ошибкой");
        return false;
    }
    try{
        initTableWidget();
    } catch(QString& str){
        qDebug(logCritical()) << str;
        // TODO proposal to close the application
    }

    return true;
}

QString DbForm::serialize(const dicomDict& data) const{

//    QDataStream ds;
//    ds.setVersion(QDataStream::Qt_5_11);
//    ds << data;
//    QString str_data;
//    ds >> str_data;
//    return str_data;
}

dicomDict DbForm::deserialize(const QString& data) const{
    QDataStream ds(data.toUtf8());
    ds.setVersion(QDataStream::Qt_5_11);
    dicomDict dict;
    ds >> dict;
    return dict;
}

void DbForm::acceptInsertSignal(QString& name, QImage& image, dicomDict& dict){
    qDebug(logDebug()) << "Signal accepted by db form";
    dumpToDb(name, image, dict);
}

DbForm::~DbForm()
{
    delete ui;
}
