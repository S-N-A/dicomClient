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


QJsonValue jsonValFromImage(const QImage& p){
    QBuffer buffer;
    buffer.open(QIODevice::WriteOnly);
    p.save(&buffer, "PNG");
    auto const encoded = buffer.data().toBase64();
    return {QLatin1String(encoded)};
}


QImage imageFrom(const QJsonValue& val){
    auto const encoded = val.toString().toLatin1();
    QImage pixmap;
    pixmap.loadFromData(QByteArray::fromBase64(encoded), "PNG");
    return pixmap;
}

}
