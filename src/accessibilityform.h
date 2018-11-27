#ifndef ACCESSIBILITYFORM_H
#define ACCESSIBILITYFORM_H

#include <QWidget>
#include <QJsonDocument>
#include <QJsonObject>

#include <QByteArray>
#include <QMessageBox>
#include <functional>

#include <telemedobject.h>
#include <senddialog.h>
#include <logger.h>

namespace Ui {
class AccessibilityForm;
}

namespace{
    const QString dialogName = "Сделать запрос";
}

class AccessibilityForm : public QWidget
{
    Q_OBJECT

public:
    explicit AccessibilityForm(QWidget *parent = nullptr);
    bool askForSave();
    ~AccessibilityForm();

public slots:
    void processIncomingData(QByteArray ba);
private slots:
    void on_requestButton_clicked();

private:
    Ui::AccessibilityForm *ui;
};

#endif // ACCESSIBILITYFORM_H
