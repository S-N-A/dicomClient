#ifndef CLIENT_H
#define CLIENT_H


#include <QObject>
#include <QTcpSocket>
#include <QThreadPool>
#include <QByteArray>
#include <logger.h>
#include <task.h>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject* parent= nullptr);
    void setSocket(qintptr Descriptor);

public slots:
    void connected();
    void disconnected();
    void readyRead();

    void TaskResult(QByteArray ba);

private:
    QTcpSocket* socket;
    const int m_max_thread_count = 5;
};

#endif // CLIENT_H
