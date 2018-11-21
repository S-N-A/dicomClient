#ifndef TELEMEDOBJECT_H
#define TELEMEDOBJECT_H

#include <QImage>
#include "tagshelpers.h"
#include <QString>
#include <QException>
#include "serializehelper.h"


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
    TeleMedObject(QImage img, dicomDict dict,
                  QString Request, QString Response);
    friend QDataStream& operator<<(QDataStream& ds, const TeleMedObject& medobj);
    friend QDataStream& operator>>(QDataStream& ds, TeleMedObject& medobj);
    ~TeleMedObject(){}
private:
    QImage m_img;
    dicomDict m_dicomDict;
    QString m_request;
    QString m_response;
};

#endif // TELEMEDOBJECT_H
