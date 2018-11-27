#ifndef TASK_H
#define TASK_H

#include <QRunnable>
#include <QByteArray>
#include <QObject>
#include <logger.h>

class Task : public QObject, public QRunnable
{
    Q_OBJECT

public:
    Task(QObject* parent=nullptr);
    void setClientInfo(const QByteArray& ba);
signals:
    void Result(QByteArray ba);
protected:
    void run();
private:
    QByteArray m_client_request;
};

#endif // TASK_H
