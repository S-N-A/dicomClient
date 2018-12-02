#ifndef SENDDIALOG_H
#define SENDDIALOG_H

#include <QDialog>
#include <QSqlError>
#include <QHostInfo>
#include <QNetworkInterface>
#include <QFile>
#include <QTcpSocket>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QIcon>
#include <QDateTime>
#include <QMessageBox>
#include  "logger.h"
#include "telemedobject.h"
#include "tablefields.h"


namespace Ui {
class SendDialog;
}

using idWithObject = QPair<TeleMedObject, int>;

namespace{
    const QString dbTable = "patient";
    const QString dbFile = "dicom.db";
    const quint16 port = 7808;
}

/*!
 * \brief Класс формы отправки запроса
 * \author Илья Трефилов
 * \date 01.12.2018
 *
 * Класс формы отправки запроса
 */
class SendDialog : public QDialog
{
    Q_OBJECT

public:
    /*!
     * \brief SendDialog
     * \param parent Указатель на родительский виджет
     *
     * Конструктор класса формы
     */
    explicit SendDialog(QWidget *parent = nullptr);
    /*!
     * \brief sendData
     * \param ba Набор байт для отправки по сети
     * \param host Ip адресс или имя хоста на который надо отправить информацию
     * \param id Номер объекта из базы данных для отправки
     *
     * Функция отправляет объект информации о клиента из базы данных в виде бинарных данных по сети
     */
    void sendData(const QByteArray& ba, const QString& host, const int& id);
    ~SendDialog();

private slots:
    /*!
     * \brief on_sendButton_clicked
     *
     * Слот принимающий нажатие на кнопку отправить и отправляющий данные. Проверки на валидность ввода реализованы
     */
    void on_sendButton_clicked();

private:
    /*!
     * \brief m_tcpSocket
     *
     * Сокет для отправки данных по сети
     */
    QTcpSocket m_tcpSocket;
    /*!
     * \brief m_nameMapping
     *
     * Объект, представляющий докумет типа JSON
     */
    QJsonDocument m_nameMapping;
    /*!
     * \brief ui
     *
     * Указатель на объект интерфейса для формы отправки данных
     */
    Ui::SendDialog *ui;
    /*!
     * \brief initTable
     * \return  true  - если удалось получить данные из таблицы  базы данных в таблицу виджета
     *
     * Функция инициализирующая таблицу с информацией из базы данных
     */
    bool initTable();
    /*!
     * \brief readConfig
     * \return Объект, представляющий json из файла
     *
     * Функция читающая файл config.json, возвращает объет типа JSON из данного файла
     * Данная функция необходима для отображения ip адресов на имена врачей
     */
    QJsonDocument readConfig() const;
    /*!
     * \brief buildTeleMedObject
     * \return Объект - пару, информация о отправляемом объекте и id из базы данных
     *
     * Функция для построения объекта, связующего информацию в запросе и номер объекта в базе данных
     */
    idWithObject buildTeleMedObject();
    /*!
     * \brief connectToHost
     * \param host ip адрес или имя хоста в сети, куда надо отправить данные
     * \return true - если подключение было успешным
     *
     * Функция для подключения к принимающему информацию хосту
     */
    bool connectToHost(const QString& host);
    /*!
     * \brief writeData
     * \param data Бинарные данные, представлюящие объект запроса
     * \return true - если запись была успешна
     *
     * Записывает данные в открытое соединение между отправляющей и принимающей стороной
     */
    bool writeData(const QByteArray& data);
    /*!
     * \brief getHost
     * \param name Имя врача
     * \return  Ip адрес или имя хоста в сети выбранного врача
     *
     * Функция для получения ip адреса по имени
     *
     */
    QString getHost(const QString& name) const;
    /*!
     * \brief updateTable
     * \param id Номер отправляемого объекта в базе данных
     * \param ba Бинарные данные, представлюящие объект запроса
     *
     * Функция обновляет данные в таблице базы данных после отправки запроса
     */
    void updateTable(const int& id, QByteArray& ba);
    /*!
     * \brief buildComboBox
     * \return true - если удалось получить имена из файла config.json для их отображения в боксе
     *
     * Функция строит бокс с выпадающим списком с именами врачей для отправки данных
     * Имя отображается на ip адрес
     */
    bool buildComboBox();

};

#endif // SENDDIALOG_H
