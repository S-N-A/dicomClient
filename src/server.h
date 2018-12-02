#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <logger.h>
#include <client.h>


/*!
 * \brief Класс сервера
 * \author Илья Трефилов
 * \date 01.12.2018
 *
 * Класс сервера для приема запросов
 */
class Server : public QTcpServer
{
    Q_OBJECT
public:
    /*!
     * \brief Server
     * \param parent Указатель на родительский объект
     *
     * Конструктор класса сервера
     */
    explicit Server(QObject* parent = nullptr);
    /*!
     * \brief startServer
     *
     * Функция для запуска сервера на порту 7808
     */
    void startServer();
protected:
    /*!
     * \brief incomingConnection
     * \param socketDescriptor Дескриптор сокета при соединении
     *
     * Функция для обработки входящего соединения и выделения необходимых системных ресурсов
     */
    void incomingConnection(qintptr socketDescriptor);
signals:
    /*!
     * \brief transferDataToWidget
     * \param ba Набор байт
     *
     * Сигнал для передачи полученной информации в класс виджет для отображения
     */
    void transferDataToWidget(QByteArray ba);
public slots:
    /*!
     * \brief GetDataFromClient
     * \param ba Набор байт
     *
     * Слот для получения информации от потока обрабатывающего соединение
     */
    void GetDataFromClient(QByteArray ba);

};

#endif // SERVER_H
