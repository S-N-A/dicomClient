#include "accessibilityform.h"
#include "ui_accessibilityform.h"

AccessibilityForm::AccessibilityForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AccessibilityForm), m_address(""), m_port(""), m_title("")
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
    qDebug(logDebug()) << "Connect options : " << this->m_address << this->m_port;
    gdcm::Directory::FilenamesType filename;
    filename.push_back("/home/ilya/test.dcm");
    if(gdcm::CompositeNetworkFunctions::CEcho(this->m_address.toStdString().c_str(),
                                           static_cast<uint16_t>(this->m_port.toInt()),
                                              [=](){if (m_title.isEmpty()){ return "test";}
                                              else {return m_title.toStdString().c_str();}}()) &&
            gdcm::CompositeNetworkFunctions::CStore("127.0.0.1",104,filename)){
        QMessageBox::information(this, m_ReqInfo, m_SuccessText);
        return;
    } else {
        QMessageBox::warning(this, m_ReqInfo, m_FailText);
        return;
    }
}



void AccessibilityForm::on_IPAddressForm_textChanged(const QString &arg1)
{
    m_address = arg1;
}



void AccessibilityForm::on_PortForm_textChanged(const QString &arg1)
{
    m_port = arg1;
}



void AccessibilityForm::on_AETitleForm_textChanged(const QString &arg1)
{
    m_title = arg1;
}

void AccessibilityForm::on_CEchoButton_clicked()
{
    checkConnection();
}
