#include "task.h"

Task::Task(QObject* parent) : QObject (parent)
{
    qDebug(logDebug) << "Task ctor called - Task::Task()";
}



void Task::run(){
    qDebug((logDebug())) << "Task started: emitting Client request to Client";
    emit Result(m_client_request);
}

void Task::setClientInfo(const QByteArray& ba){
    m_client_request = ba;
    qDebug(logDebug()) << "m_client_request: " << m_client_request;
}
