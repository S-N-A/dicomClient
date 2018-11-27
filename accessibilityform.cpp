#include "accessibilityform.h"
#include "ui_accessibilityform.h"

AccessibilityForm::AccessibilityForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AccessibilityForm)
{
    ui->setupUi(this);
}

AccessibilityForm::~AccessibilityForm()
{
    delete ui;
}


