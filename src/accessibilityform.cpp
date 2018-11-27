#include "accessibilityform.h"
#include "ui_accessibilityform.h"

AccessibilityForm::AccessibilityForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AccessibilityForm)
{
 //   connect(this, saveToDb)
    ui->setupUi(this);
}

AccessibilityForm::~AccessibilityForm()
{
    delete ui;
}


void AccessibilityForm::processIncomingData(QByteArray ba){
    QJsonDocument doc;
    doc.fromBinaryData(ba);
    if (doc.isNull()){
        QMessageBox::critical(this, "Ошибка", "Невозможно обработать полученную информацию", QMessageBox::Ok);
        return;
    }
    TeleMedObject obj(doc);
    if (obj.isEmpty()){
        QMessageBox::critical(this, "Ошибка", "Невозможно обработать полученную информацию", QMessageBox::Ok);
        return;
    }
    if(askForSave()){
        //Todo
    }


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
