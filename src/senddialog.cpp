#include "senddialog.h"
#include "ui_senddialog.h"

SendDialog::SendDialog(QWidget *parent) :
    QDialog(parent),
    m_tcpSocket(new QTcpSocket(this)),
    ui(new Ui::SendDialog)
{
    ui->setupUi(this);
    initTable();
}

SendDialog::~SendDialog()
{
    delete ui;
}


bool SendDialog::initTable(){
    QSqlQuery query;
    QStringList headers;


    query.prepare("SELECT * FROM " + ::dbTable);
    if(!query.exec()){
            qDebug(logCritical()) << "Critical DB error - Couldn't exec last query";
            return false;
    }

    qDebug(logDebug()) << query.lastQuery();
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setRowCount(100); // No support for size() in sqlite
    qDebug(logDebug()) << "Query record count - " << query.record().count();
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    headers << "Id" << "Пациент";
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    for (int counter = 0; query.next(); counter++){
        QTableWidgetItem *id = new QTableWidgetItem(query.value(0).toString());
        QTableWidgetItem *name = new QTableWidgetItem(query.value(1).toString());
        ui->tableWidget->setItem(counter, static_cast<int>(0), id);
        id->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        ui->tableWidget->setItem(counter, static_cast<int>(1), name);
        name->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    }
    return true;

}

void SendDialog::on_pushButton_clicked()
{
    if(ui->requestEdit->text().isEmpty() || ui->ipLineEdit->text().isEmpty()){
        QMessageBox::warning(this, "Ошибка", "Поле запроса пустое");
        return;
    }

}
