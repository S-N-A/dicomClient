#include "accessibilityform.h"
#include "ui_accessibilityform.h"

AccessibilityForm::AccessibilityForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AccessibilityForm)
{
    scene = new QGraphicsScene();
    ui->setupUi(this);
    ui->responseButton->setEnabled(false);
}

AccessibilityForm::~AccessibilityForm()
{
    delete scene;
    delete ui;
}



bool AccessibilityForm::askForSave(){
    QMessageBox box;
    box.setText("Сохранение в базу");
    box.setInformativeText("Был получен новый запрос. Сохранить в локальную базу?");
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

void AccessibilityForm::on_requestButton_clicked()
{
    SendDialog dialog;
    dialog.setWindowTitle(::dialogName);
    dialog.exec();
}

void AccessibilityForm::getDataFromServer(QByteArray ba){
    QJsonDocument doc = QJsonDocument::fromBinaryData(ba);
    try{
    TeleMedObject telemedobj(doc);
    m_current_telemedobj = telemedobj;
    dicomDict tmpDict = m_current_telemedobj.getDicomDict();
    QString tmpName = getNameFromDict(tmpDict);\
    QImage tmpImg = m_current_telemedobj.getImage();
    addInfoMap tmpMap = m_current_telemedobj.getInfoMap();
    if(askForSave()){
        qDebug(logDebug()) << "sendSignalToDump called with - " << m_current_telemedobj.toJson();
        emit sendSignalToDump(tmpName, tmpImg, tmpDict, tmpMap);
    }
    showCurrentObj();
    qDebug(logDebug()) << telemedobj.toJson();
    qDebug(logDebug()) << "Transfer successful";
    } catch(const TeleMedObjException& exc){
        qDebug(logCritical()) << exc.what();
        return;
    }

}


void AccessibilityForm::showCurrentObj(){
    QImage image = m_current_telemedobj.getImage();
    dicomDict  dict = m_current_telemedobj.getDicomDict();
    addInfoMap infoMap = m_current_telemedobj.getInfoMap();

    // Working with scene
    scene->clear();
    scene->addPixmap(QPixmap::fromImage(image));
    ui->requestImageView->setScene(scene);
    ui->requestImageView->update();

    ui->requestField->clear();
    ui->requestField->setText(infoMap["request"]);

    // Set response to read only if it was an answer
    if(!infoMap["response"].isEmpty()){
        ui->responseField->setReadOnly(true);
        ui->responseField->setText(infoMap["response"]);
    }

    ui->dateLabel->clear();
    ui->dateLabel->setText("Время запроса: " + infoMap["request_date"]);

    ui->requesterLabel->clear();
    ui->requesterLabel->setText("Запрос поступил от " + infoMap["requester"]);

    ui->responseButton->setEnabled(true);

    DbForm::initFooterTable(ui->dicomTableWidget, dict);

}

void AccessibilityForm::on_responseButton_clicked()
{
    if(ui->responseField->toPlainText().isEmpty()){
        QMessageBox::critical(this, "Ошибка","Поле с ответом не заполнено");
    }
    SendDialog dialog;

    QImage tmpImg = m_current_telemedobj.getImage();
    dicomDict tmpDicomDict = m_current_telemedobj.getDicomDict();
    addInfoMap tmpInfoMap = m_current_telemedobj.getInfoMap();
    QString ip_address;
    foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost))
             ip_address = address.toString();
    }
    tmpInfoMap["responser"] = ip_address;
    tmpInfoMap["response_date"] = QDateTime::currentDateTime().toString();
    tmpInfoMap["response"] = ui->responseField->toPlainText();
    TeleMedObject tmpObj = TeleMedObject(tmpImg, tmpDicomDict, tmpInfoMap);
    auto ba = tmpObj.toJson().toBinaryData();
    dialog.sendData(ba, tmpInfoMap["requester"], 1);
}
