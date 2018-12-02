#include "client.h"

Client::Client(QObject* parent) : QObject (parent)
{
    QThreadPool::globalInstance()->setMaxThreadCount(m_max_thread_count);

}

void Client::setSocket(qintptr Descriptor){
    socket = new QTcpSocket(this);
    qDebug(logDebug()) << "New socket created";
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    socket->setSocketDescriptor(Descriptor);
    qDebug(logDebug()) << "Client connected at " << Descriptor;

}


void Client::connected(){
    qDebug(logDebug()) << "Client connected";
}

void Client::disconnected(){
    qDebug(logDebug()) << "Client disconnected";
}

void Client::readyRead(){
    qDebug(logDebug()) << "Client::readyRead()";

    Task* task = new Task();
    task->setAutoDelete(true);
    task->setClientInfo(socket->readAll());
    connect(task, SIGNAL(Result(QByteArray)), this, SLOT(TaskResult(QByteArray)), Qt::QueuedConnection);
    qDebug(logDebug()) << "Starting task with thread from pool";
    QThreadPool::globalInstance()->start(task);

}


void Client::TaskResult(QByteArray ba){
    qDebug(logDebug()) << "Client::TaskResult : " << ba;
    emit transferDataToServer(ba);
}
