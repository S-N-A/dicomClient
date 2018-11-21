#include "telemedobject.h"

namespace  {
    const QDataStream::Version SerVersion = QDataStream::Qt_5_11;
}

TeleMedObject::TeleMedObject(QImage img, dicomDict dict,
              QString Request, QString Response) : m_img(img),
    m_dicomDict(dict), m_request(Request), m_response(Response)
{
    if(m_dicomDict.isEmpty() || m_img.isNull()){
        throw TeleMedObjException("Couldn't initialize object with empty image and dict");
    }
}


QDataStream& operator<<(QDataStream& ds, const TeleMedObject& medobj){


//    QByteArray ImageBa = Serialize::imageToByteArray(medobj.m_img);
//    QByteArray dicomDictBa = Serialize::dicomDataToByteArray(medobj.m_dicomDict);
//    ds.setVersion(SerVersion);
//    ds << ImageBa ;//<< dicomDictBa;//<< medobj.m_request << medobj.m_response;
//    return ds;
}

QDataStream& operator>>(QDataStream& ds, TeleMedObject& medobj){
//    QByteArray ImageBa;
//    QByteArray dicomDictBa;
//    QByteArray test_ba;
//    ds >> test_ba;
//    qDebug(logDebug()) << test_ba.data();
//    ds >> ImageBa >> dicomDictBa >> medobj.m_request >> medobj.m_response;
//    medobj.m_img = Serialize::byteArrayToImage(ImageBa);
//    medobj.m_dicomDict = Serialize::byteArrayToDicomData(&dicomDictBa);
//    if (medobj.m_img.isNull() || medobj.m_dicomDict.isEmpty()){
//        throw TeleMedObjException("Serialization failed because image or dict is corrupted");
//    }
//    return  ds;
}
