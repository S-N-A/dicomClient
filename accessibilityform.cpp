#include "accessibilityform.h"
#include "ui_accessibilityform.h"

AccessibilityForm::AccessibilityForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AccessibilityForm)
{
    m_address = "";
    m_port="";
    m_title="";
    ui->setupUi(this);
}

AccessibilityForm::~AccessibilityForm()
{
    delete ui;
}


void AccessibilityForm::checkConnection(){
    if(gdcm::CompositeNetworkFunctions::CEcho(this->m_address.toStdString().c_str(),
                                           static_cast<uint16_t>(this->m_port.toInt()),
                                              this->m_title.toStdString().c_str())){
        QMessageBox::information(this, m_ReqInfo, m_SuccessText);
        return;
    } else {
        QMessageBox::warning(this, m_ReqInfo, m_FailText);
        return;
    }
}


template<typename T>
void AccessibilityForm::checkEquality(T a, T b){
    if (a == b){
        return;
    } else{
        b = a;
        return;
    }
}

void AccessibilityForm::on_IPAddressForm_textChanged(const QString &arg1)
{
    checkEquality(arg1, m_address);
}



void AccessibilityForm::on_PortForm_textChanged(const QString &arg1)
{
    checkEquality(arg1, m_port);
}



void AccessibilityForm::on_AETitleForm_textChanged(const QString &arg1)
{
    checkEquality(arg1, m_title);
}

void AccessibilityForm::on_CEchoButton_clicked()
{
    checkConnection();
}
