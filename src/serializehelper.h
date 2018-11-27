
#ifndef SERIALIZEHELPER_H
#define SERIALIZEHELPER_H

#include <QPixmap>
#include <QByteArray>
#include <QImage>
#include <QJsonValue>
#include <QPixmap>
#include <QBuffer>
#include <tagshelpers.h>
#include <QScopedPointer>

using addInfoMap = QMap<QString, QString>;

namespace  Serialize{


QByteArray imageToByteArray(const QImage &image);
QImage byteArrayToImage(const QByteArray &ba);
QJsonValue jsonValFromImage(const QImage& p);
QImage imageFrom(const QJsonValue& val);

template <class T>
auto dictToByteArray(const T& dict) -> QByteArray{
    QByteArray ba;
    QScopedPointer<QDataStream> dsPointer(new  QDataStream(&ba, QIODevice::WriteOnly));
    (*dsPointer) << dict;
    return ba;
}

template <class T>
T byteArrayToDict(QByteArray* ba){
    T dict;
    QScopedPointer<QDataStream> dsPointer(new QDataStream(ba, QIODevice::ReadOnly));
    (*dsPointer) >> dict;
    return dict;
}
template <class T>
T dictFromBase64(const QJsonValue& value){
    auto const encoded = value.toString().toLatin1();
    QByteArray ba = QByteArray::fromBase64(encoded);
    T dict = byteArrayToDict<T>(&ba);
    return dict;
}
}
#endif // SERIALIZEHELPER_H
