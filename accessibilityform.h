#ifndef ACCESSIBILITYFORM_H
#define ACCESSIBILITYFORM_H

#include <QWidget>
#include <QMessageBox>

#include <logger.h>

namespace Ui {
class AccessibilityForm;
}

class AccessibilityForm : public QWidget
{
    Q_OBJECT

public:
    explicit AccessibilityForm(QWidget *parent = nullptr);
    ~AccessibilityForm();


private:
    Ui::AccessibilityForm *ui;
};

#endif // ACCESSIBILITYFORM_H
