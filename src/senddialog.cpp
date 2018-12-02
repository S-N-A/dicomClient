#include "senddialog.h"
#include "ui_senddialog.h"

SendDialog::SendDialog(QWidget *parent) :
    QDialog(parent),
    m_tcpSocket(new QTcpSocket(this)),
    m_nameMapping(readConfig()),
    ui(new Ui::SendDialog)
{
    ui->setupUi(this);
    initTable();
    if(!buildComboBox()){
        QMessageBox::critical(this, "Ошибка", "Ошибка при чтении файла конфигурации");
    }
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



void SendDialog::on_sendButton_clicked()
{
    if(ui->requestEdit->text().isEmpty()){
        QMessageBox::warning(this, "Ошибка", "Поле запроса пустое");
        return;
    }
    idWithObject idWithObj = buildTeleMedObject();
    if(idWithObj.first.isEmpty()){
        return;
    }
    auto json = idWithObj.first.toJson();
    auto binData = json.toBinaryData();
    sendData(binData, getHost(idWithObj.first.getResponser()), idWithObj.second);
}

idWithObject SendDialog::buildTeleMedObject(){
    int chosenId = ui->tableWidget->currentRow() + 1;
    QSqlQuery query;
    query.prepare("SELECT * FROM " + ::dbTable + " WHERE id=" + QString::number(chosenId));
    if(!query.exec()){
        qDebug(logCritical()) << query.lastQuery();
        qDebug(logCritical()) << "Couldn't query by id=" << QString::number(chosenId);
        QMessageBox::critical(this, "Ошибка", "Ошибка обращения к базе данных");
        return idWithObject();
    }
    qDebug(logDebug()) << query.lastQuery();
    query.first();
    QImage img = Serialize::byteArrayToImage(query.value(tableFields::table_image).toByteArray());
    QByteArray data = query.value(tableFields::table_data).toByteArray();
    dicomDict dict = Serialize::byteArrayToDict<dicomDict>(&data);
    addInfoMap map;
    map["request"] = ui->requestEdit->text();
    map["request_date"] = QDateTime::currentDateTime().toString();
    QString ip_address;
    foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost))
             ip_address = address.toString();
    }
    map["requester"] = ip_address;
    map["responser"] = ui->nameComboBox->currentText();
    try {
        TeleMedObject teleMedObj = TeleMedObject(img, dict, map);
        return idWithObject(teleMedObj, chosenId);
    } catch (const TeleMedObjException& exc) {
        qDebug(logCritical()) << exc.what();
        QMessageBox::warning(this, "Предупреждение", "Необходимо выбрать объект для отправки из базы банных");
        return idWithObject(TeleMedObject(), chosenId);
    }
}

bool SendDialog::buildComboBox(){
    if(m_nameMapping.isEmpty()){
        return false;
    }
    QJsonObject json = m_nameMapping.object();
    QStringList nameList;
    for(auto value: json.keys()){
        nameList << value;
    }
    ui->nameComboBox->addItems(nameList);
    return true;
}

QJsonDocument SendDialog::readConfig() const {
    QFile file;
    file.setFileName("config.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString text = file.readAll();
    file.close();
    QJsonDocument nameMapping = QJsonDocument::fromJson(text.toUtf8());
    return nameMapping;
}


void SendDialog::sendData(const QByteArray& ba, const QString& host, const int& id){
    if(!connectToHost(host)){
        qDebug(logCritical()) << "Couldn't connect to host - " << host << " with port - " << QString::number(::port);
        QMessageBox::critical(this, "Ошибка", "Ошибка создания подключения");
        return;
    }
    if(!writeData(ba)){
        qDebug(logCritical()) << "Couldn't send data for some reason";
        QMessageBox::critical(this, "Ошибка", "Ошибка при отпралении данных");
        return;
    } else {
        QMessageBox::information(this, "Успех", "Данные были успешно отправлены");
        updateTable(id, const_cast<QByteArray&>(ba));
        return;
    }
}


bool SendDialog::connectToHost(const QString& host){
    m_tcpSocket.connectToHost(host, ::port);
    return m_tcpSocket.waitForConnected();
}

bool SendDialog::writeData(const QByteArray& data){
    if(m_tcpSocket.state() == QAbstractSocket::ConnectedState){
        m_tcpSocket.write(data);
        return m_tcpSocket.waitForBytesWritten();
    } else{
        return false;
    }
}

QString SendDialog::getHost(const QString& name) const{
    auto ip = m_nameMapping[name];
    return ip.toString();
}

void SendDialog::updateTable(const int& id, QByteArray& ba){
    QSqlQuery query;
    QJsonDocument json = QJsonDocument::fromBinaryData(ba);
    TeleMedObject obj(json);
    addInfoMap infoMap = obj.getInfoMap();
    QString request = infoMap["request"];
    QString requestDate = infoMap["request_date"];
    QString requester = infoMap["requester"];
    query.prepare("UPDATE " + ::dbTable + " SET request='" + request + "' ,request_date='" + requestDate
                  + "' ,requester='" + requester + "' WHERE ID=" + QString::number(id));
    if(!query.exec()){
        qDebug(logCritical()) << query.lastError();
        qDebug(logCritical()) << "Couldn't update table with following content " << request << endl << requestDate << endl << requester;
        qDebug(logCritical()) << "Last query: " << query.lastQuery();
    } else{
        qDebug(logInfo()) << "Last query: " << query.lastQuery();
    }
}
