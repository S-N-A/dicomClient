#ifndef CLIENT_H
#define CLIENT_H


#include <QObject>
#include <QTcpSocket>
#include <QThreadPool>
#include <QByteArray>
#include <logger.h>
#include <task.h>

/*!
 * \brief Класс имитирующий клиента подключенного к серверу
 * \author Илья Трефилов
 * \date 01.12.2018
 *
 * Данный класс предназначен для сохранения и обработки информации от подключенного клиента с сохранением контекста
 */
class Client : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief Client
     * \param parent Ссылка на родительский объект типа QObject
     *
     * Конструктор класса Client
     */
    explicit Client(QObject* parent= nullptr);
    /*!
     * \brief setSocket
     * \param Descriptor Дескриптор открытого для соединения сокета
     *
     * Данная функция создает сокет при подключении клиента к серверу
     */
    void setSocket(qintptr Descriptor);

public slots:
    /*!
     * \brief connected
     *
     * Слот для записи в лог факт соединения с клиентом
     */
    void connected();
    /*!
     * \brief disconnected
     *
     * Слот для записи в лог факт о завершении соединения с клиентом
     */
    void disconnected();
    /*!
     * \brief readyRead
     * Слот для записи в лог факта готовности к обмену информацией
     */
    void readyRead();

    /*!
     * \brief TaskResult
     * \param ba Набор байт записанный клиентом в сокет
     *
     * Слот для записи в лог полученной информации и вызова сигнала для передачи информации классу сервера
     */
    void TaskResult(QByteArray ba);
signals:
    /*!
     * \brief transferDataToServer
     * \param ba Набор байт записанный клиентом в сокет
     *
     * Сигнал отправки полученных данных классу сервера
     */
    void transferDataToServer(QByteArray ba);
private:
    /*!
     * \brief socket
     *
     * Указатель на открытый для соединения сокет
     */
    QTcpSocket* socket;
    /*!
     * \brief m_max_thread_count
     *
     * Константа ограничивающая максимальное количество одновременных потоков для обработки информации.
     * Константа создает ограничение на количество одновременно подключенных пользователей
     */
    const int m_max_thread_count = 5;
};

#endif // CLIENT_H
