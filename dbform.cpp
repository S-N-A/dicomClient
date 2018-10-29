#include "dbform.h"
#include "ui_dbform.h"

DbForm::DbForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DbForm), m_dbPath("dicomdb.db")
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
    query.prepare("SELECT * FROM :table");
    query.bindValue(":table", m_tableName);
    query.exec();

    ui->dbTableWidget->setColumnCount(query.record().count());
    qDebug(logDebug()) << "Query record count - " << query.record().count();
    ui->dbTableWidget->setRowCount(query.size());
    qDebug(logDebug()) << "Query row count - " <<query.size();
    ui->dbTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    QStringList headers;
    for(int index=0; index< query.record().count(); index++){
        headers << query.record().fieldName(index);
    }
    ui->dbTableWidget->setHorizontalHeaderLabels(headers);
    return true;
}



DbForm::~DbForm()
{
    delete ui;
}
