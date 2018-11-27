
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

namespace  Serialize{


QByteArray imageToByteArray(const QImage &image);
QImage byteArrayToImage(const QByteArray &ba);
QByteArray dicomDataToByteArray(const dicomDict &dict);
dicomDict byteArrayToDicomData(QByteArray* ba);
QJsonValue jsonValFromImage(const QImage& p);
QImage imageFrom(const QJsonValue& val);
dicomDict dictFromBase64(const QJsonValue& value);
}
#endif // SERIALIZEHELPER_H
