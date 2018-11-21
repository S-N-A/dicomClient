#include "mainwindow.h"
#include <QApplication>
#include <QScopedPointer>
#include <QFile>
#include <QLoggingCategory>
#include <QDateTime>
#include <QTextStream>
#include <server.h>

static QScopedPointer<QFile> m_logFile;

void messageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg);



int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    m_logFile.reset(new QFile("./logDicomClient.txt"));
    m_logFile.data()->open(QFile::Append | QFile::Text);
    qInstallMessageHandler(messageHandler);
    Server server;
    server.startServer();

    MainWindow w;
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
