#ifndef ACCESSIBILITYFORM_H
#define ACCESSIBILITYFORM_H

#include <QWidget>
#include <QMessageBox>
#include <gdcmCompositeNetworkFunctions.h>

namespace Ui {
class AccessibilityForm;
}

class AccessibilityForm : public QWidget
{
    Q_OBJECT

public:
    void checkConnection();
    template<typename T>
    void checkEquality(T a, T b);
    explicit AccessibilityForm(QWidget *parent = nullptr);
    ~AccessibilityForm();

private slots:
    void on_IPAddressForm_textChanged(const QString &arg1);

    void on_PortForm_textChanged(const QString &arg1);

    void on_AETitleForm_textChanged(const QString &arg1);

    void on_CEchoButton_clicked();

private:
    const QString m_ReqInfo = "Информация по запросу";
    const QString m_SuccessText = "Успешно";
    const QString m_FailText = "Запрос завершился с ошибкой";
    QString m_address, m_port, m_title;
    Ui::AccessibilityForm *ui;
};

#endif // ACCESSIBILITYFORM_H
