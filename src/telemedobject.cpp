#include "telemedobject.h"

namespace  {
    const QDataStream::Version SerVersion = QDataStream::Qt_5_11;
}

TeleMedObject::TeleMedObject(QImage img, dicomDict dict, addInfoMap map) : m_img(img),
    m_dicomDict(dict), m_addInfoMap(map)
{
    if(m_dicomDict.isEmpty() || m_img.isNull()){
        throw TeleMedObjException("Couldn't initialize object with empty image and dict");
    }
}

TeleMedObject::TeleMedObject(const QJsonDocument& doc){
    try{
    QJsonObject obj = doc.object();
    m_img = Serialize::imageFrom(obj["image"]);
    m_dicomDict = Serialize::dictFromBase64<dicomDict>(obj["dictionary"]);
    m_addInfoMap =Serialize::dictFromBase64<addInfoMap>(obj["infoMap"]);
    } catch (...){
        qDebug(logCritical()) << "Невозможно обработать полученную информацию";
    }
}


QJsonDocument TeleMedObject::toJson(){
    QJsonObject obj;
    obj["image"] = Serialize::jsonValFromImage(m_img);
    obj["dictionary"] = QLatin1String(Serialize::dictToByteArray<dicomDict>(m_dicomDict).toBase64());
    obj["infoMap"] = QLatin1String(Serialize::dictToByteArray<addInfoMap>(m_addInfoMap).toBase64());
    QJsonDocument doc(obj);
    return doc;
}


bool TeleMedObject::isEmpty(){
    if (m_img.isNull() || m_dicomDict.isEmpty()){
        return true;
    } else {
        return false;
    }
}
