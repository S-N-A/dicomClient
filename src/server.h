#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <logger.h>
#include <client.h>

class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(QObject* parent = nullptr);
    void startServer();
protected:
    void incomingConnection(qintptr socketDescriptor);
signals:

public slots:

};

#endif // SERVER_H
