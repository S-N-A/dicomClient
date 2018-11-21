#include "server.h"

Server::Server(QObject* parent) : QTcpServer (parent)
{

}

void Server::startServer(){
    if(listen(QHostAddress::Any, 7808)){
        qDebug(logDebug()) << "Server started on port: " << this->serverPort();
    } else{
        qDebug(logCritical()) << "Server not started";
    }
}

void Server::incomingConnection(qintptr socketDescriptor){
    // Make client
    Client* client = new Client(this);
    client->setSocket(socketDescriptor);
}
