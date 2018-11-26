#include <serializehelper.h>

namespace  Serialize{

QByteArray imageToByteArray(const QImage &image){
    QPixmap pixmap(QPixmap::fromImage(image));
    QByteArray imageByteArray;
    QBuffer inBuffer ( &imageByteArray );
    inBuffer.open(QIODevice::WriteOnly);
    pixmap.save(& inBuffer , "PNG");
    return imageByteArray;
}

QImage byteArrayToImage(const QByteArray &ba){
    QPixmap outPixMap = QPixmap();
    outPixMap.loadFromData( ba );
    return outPixMap.toImage();
}

QByteArray dicomDataToByteArray(const dicomDict &dict){
    QByteArray ba;
    QScopedPointer<QDataStream> dsPointer(new  QDataStream(&ba, QIODevice::WriteOnly));
    (*dsPointer) << dict;
    return ba;
}
dicomDict byteArrayToDicomData(QByteArray* ba){
    dicomDict dict;
    QScopedPointer<QDataStream> dsPointer(new QDataStream(ba, QIODevice::ReadOnly));
    (*dsPointer) >> dict;
    return dict;
}
QJsonValue jsonValFromImage(const QImage& p){
    QBuffer buffer;
    buffer.open(QIODevice::WriteOnly);
    p.save(&buffer, "PNG");
    auto const encoded = buffer.data().toBase64();
    return {QLatin1String(encoded)};
}

dicomDict dictFromBase64(const QJsonValue& value){
    auto const encoded = value.toString().toLatin1();
    QByteArray ba = QByteArray::fromBase64(encoded);
    dicomDict dict = byteArrayToDicomData(&ba);
    return dict;
}

QImage imageFrom(const QJsonValue& val){
    auto const encoded = val.toString().toLatin1();
    QImage pixmap;
    pixmap.loadFromData(QByteArray::fromBase64(encoded), "PNG");
    return pixmap;
}

}
