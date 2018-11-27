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

TeleMedObject::TeleMedObject(const QJsonDocument& doc){

    QJsonObject obj = doc.object();
    m_img = Serialize::imageFrom(obj["image"]);
    m_dicomDict = Serialize::dictFromBase64(obj["dictionary"]);
    m_request = obj["request"].toString();
    m_response = obj["response"].toString();
    }


QJsonDocument TeleMedObject::toJson(){
    QJsonObject obj;
    obj["image"] = Serialize::jsonValFromImage(m_img);
    obj["dictionary"] = QLatin1String(Serialize::dicomDataToByteArray(m_dicomDict).toBase64());
    obj["request"] = m_request;
    obj["response"] = m_response;
    QJsonDocument doc(obj);
    return doc;
}


