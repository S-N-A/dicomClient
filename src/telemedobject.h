#ifndef TELEMEDOBJECT_H
#define TELEMEDOBJECT_H

#include <QImage>
#include <QMap>
#include <QTextCodec>
#include <QMessageBox>
#include "tagshelpers.h"
#include <QString>
#include <QException>
#include <QJsonObject>
#include <QJsonDocument>
#include "serializehelper.h"


using addInfoMap = QMap<QString, QString>;
class TeleMedObjException : public QException{
public:
    TeleMedObjException(const char* errorString) : m_errorString(errorString){}
    virtual void raise() const{throw *this;}
    virtual TeleMedObjException *clone() const{return new TeleMedObjException(*this);}
    virtual const char* what() const noexcept{return m_errorString;}
private:
    const char* m_errorString;
};


class TeleMedObject
{

public:
    TeleMedObject(){}
    TeleMedObject(QImage img, dicomDict dict, addInfoMap map);
    TeleMedObject(const QJsonDocument& doc);
    QJsonDocument toJson();
    bool isEmpty();

    ~TeleMedObject(){}
private:
    QImage m_img;
    dicomDict m_dicomDict;
    addInfoMap m_addInfoMap;
};

#endif // TELEMEDOBJECT_H
