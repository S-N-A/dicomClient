#ifndef ACCESSIBILITYFORM_H
#define ACCESSIBILITYFORM_H

#include <QWidget>
#include <QJsonDocument>
#include <QJsonObject>

#include <QByteArray>
#include <QMessageBox>
#include <QGraphicsScene>

#include <telemedobject.h>
#include <senddialog.h>
#include <logger.h>
#include "server.h"

#include "dbform.h"

namespace Ui {
class AccessibilityForm;
}

namespace{
    const QString dialogName = "Сделать запрос";
}
/*!
 * \brief Класс формы для осуществления сетевого взаимодействия.
 * \author Илья Трефилов
 * \date 01.12.2018
 * \todo Запись в базу объекта ответа
 *
 * Данный класс предназначен для управления функциями, виджета "Сетевое взаимодействие"
 */
class AccessibilityForm : public QWidget
{
    Q_OBJECT

public:
    /*!
     * \brief AccessibilityForm
     * \param parent
     *
     * Конструтор класса, принимающий в параметре ссылку на родительский виджет
     */
    explicit AccessibilityForm(QWidget *parent = nullptr);
    /*!
     * \brief askForSave
     * \return Возвращает значение типа boolean, указывающее на необходимость сохранения в базу данных
     *
     * Если функция вернула true - посылаем сигнал сохранения в базу данных
     */
    bool askForSave();
    QGraphicsScene* scene;
    ~AccessibilityForm();
signals:
    /*!
     * \brief sendSignalToDump
     * \param name Имя пациента
     * \param image Медицинское изображение
     * \param dict Словарь, содержащий значения тегов исходного файла формата dicom
     * \param map Словарь, содержащий дополнительную информацию о запросе\ответе
     */
    void sendSignalToDump(QString& name, QImage& image, dicomDict& dict, addInfoMap& map);
public slots:
    /*!
     * \brief getDataFromServer
     * \param ba Набор байт, сформированный при отправке сообщения
     *
     * Функция принимает присланные данные от запрашивающего и обрабатывает их
     */
    void getDataFromServer(QByteArray ba);
private slots:
    /*!
     * \brief on_requestButton_clicked
     *
     * Слот отображающий форму отправки запроса, при нажатии на кнопку "Сделать запрос"
     */
    void on_requestButton_clicked();
    /*!
     * \brief on_responseButton_clicked
     *
     * Слот, который собирает информацию с виджета, после нажатия на кнопку "Ответить" для последующей отправки
     */
    void on_responseButton_clicked();

private:
    /*!
     * \brief m_current_telemedobj
     *
     * Объект запроса, отображаемый на виджете
     */
    TeleMedObject m_current_telemedobj;
    /*!
     * \brief ui
     *
     * Указатель на объект интерфейса для виджета
     */
    Ui::AccessibilityForm *ui;
    /*!
     * \brief showCurrentObj
     *
     * Функция отображающая объект запроса на виджете. Объект запроса берется из m_current_telemedobj
     */
    void showCurrentObj();
};

#endif // ACCESSIBILITYFORM_H
