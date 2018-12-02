#include "mainwindow.h"
#include <QApplication>
#include <QSystemSemaphore>
#include <QSharedMemory>
#include <QScopedPointer>
#include <QFile>
#include <QLoggingCategory>
#include <QDateTime>
#include <QTextStream>

#include "server.h"

namespace {
    QScopedPointer<QFile> m_logFile;
}

void messageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg);


int main(int argc, char *argv[]) {

    QApplication a(argc, argv);

    QSystemSemaphore semaphore("8927843", 1);
    semaphore.acquire();

#ifndef Q_OS_WIN32
    QSharedMemory nix_fix_shared_memory("2857289");
    if(nix_fix_shared_memory.attach()){
        nix_fix_shared_memory.detach();
    }
#endif
    QSharedMemory sharedMemory("2857289");
    bool is_running;
    if(sharedMemory.attach()){
        is_running = true;
    } else{
        sharedMemory.create(1);
        is_running = false;
    }
    semaphore.release();
    if(is_running){
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("Приложение уже запущено");
        msgBox.exec();
        return 1;
    }

    m_logFile.reset(new QFile("./log.txt"));
    m_logFile.data()->open(QFile::Append | QFile::Text);
    qInstallMessageHandler(messageHandler);

    Server server;
    server.startServer();
    MainWindow w;
    auto acForm = w.children().at(1)->children().at(2);
    qDebug(logDebug()) << w.children().at(1)->children().at(2);
    QObject::connect(&server, SIGNAL(transferDataToWidget(QByteArray)), acForm, SLOT(getDataFromServer(QByteArray)));
    w.show();
    return a.exec();
}

void messageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{

    QTextStream out(m_logFile.data());
    
    out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz ");

    switch (type)
    {
    case QtInfoMsg:     out << "INF "; break;
    case QtDebugMsg:    out << "DBG "; break;
    case QtWarningMsg:  out << "WRN "; break;
    case QtCriticalMsg: out << "CRT "; break;
    case QtFatalMsg:    out << "FTL "; break;
    }

    out << context.category << ": "
        << msg << endl;
    out.flush();
}
