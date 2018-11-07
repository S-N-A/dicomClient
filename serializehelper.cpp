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
}
