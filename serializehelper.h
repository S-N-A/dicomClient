
#ifndef SERIALIZEHELPER_H
#define SERIALIZEHELPER_H

#include <QPixmap>
#include <QByteArray>
#include <QImage>
#include <QBuffer>
#include <tagshelpers.h>
#include <QScopedPointer>

namespace  Serialize{


QByteArray imageToByteArray(const QImage &image);
QImage byteArrayToImage(const QByteArray &ba);
QByteArray dicomDataToByteArray(const dicomDict &dict);
dicomDict byteArrayToDicomData(QByteArray* ba);
}
#endif // SERIALIZEHELPER_H
