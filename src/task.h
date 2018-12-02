#ifndef TASK_H
#define TASK_H

#include <QRunnable>
#include <QByteArray>
#include <QObject>
#include <logger.h>

/*!
 * \brief Класс задачи
 * \author Илья Трефилов
 * \date 01.12.2018
 *
 * Класс задачи выполняемой в отдельном потоке
 */
class Task : public QObject, public QRunnable
{
    Q_OBJECT

public:
    /*!
     * \brief Task
     * \param parent Указатель на родительский объект
     *
     * Конструктор класса задачи
     */
    Task(QObject* parent=nullptr);
    /*!
     * \brief setClientInfo
     * \param ba Набор байт
     *
     * Функция для сохранения полученного набора данных из сетевого взаимодействия в память
     */
    void setClientInfo(const QByteArray& ba);
signals:
    /*!
     * \brief Result
     * \param ba Набор байт
     *
     * Функция для отправки сигнала из отдельного потока в вызывающий объект типа Client
     */
    void Result(QByteArray ba);
protected:
    /*!
     * \brief run
     *
     * Функция для запуска отдельного потока при обработке информации полученной при сетевом взаимодействии
     */
    void run();
private:
    /*!
     * \brief m_client_request
     *
     * Набор байт в запросе, сохраненный в память
     */
    QByteArray m_client_request;
};

#endif // TASK_H
