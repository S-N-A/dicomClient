
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

/*!
 * \brief imageToByteArray
 * \param image Изображение
 * \return Набор байт
 *
 * Функция сериализует объект изображения  в бинарные данные
 */
QByteArray imageToByteArray(const QImage &image);
/*!
 * \brief byteArrayToImage
 * \param ba Набор байт
 * \return Изображение
 *
 * Функция конвертирует бинарные данные в изображение
 */
QImage byteArrayToImage(const QByteArray &ba);
/*!
 * \brief jsonValFromImage
 * \param p Изображение
 * \return Объект типа ключ в структуре json
 *
 * Функция конвертирует изображение в тип ключ значение, где ключ - image, значение - бинарные данные
 */
QJsonValue jsonValFromImage(const QImage& p);
/*!
 * \brief imageFrom
 * \param val Ключ - значение с изображение
 * \return Объект изображения
 *
 * Функция тип ключ значение, где ключ - image, значение - бинарные данные в объект изображения
 */
QImage imageFrom(const QJsonValue& val);


/*!
 * \brief dictToByteArray
 *
 * Шаблон для сериализации типа словарь в бинарные данные
 */
template <class T>
auto dictToByteArray(const T& dict) -> QByteArray{
    QByteArray ba;
    QScopedPointer<QDataStream> dsPointer(new  QDataStream(&ba, QIODevice::WriteOnly));
    (*dsPointer) << dict;
    return ba;
}

/*!
 * \brief byteArrayToDict
 *
 * Шаблон для сериализации бинарных данных в словарь
 */
template <class T>
T byteArrayToDict(QByteArray* ba){
    T dict;
    QScopedPointer<QDataStream> dsPointer(new QDataStream(ba, QIODevice::ReadOnly));
    (*dsPointer) >> dict;
    return dict;
}


/*!
 * \brief dictFromBase64
 *
 * Шаблон для сериализации бинарных данных в кодировке basе64 в словарь
 */
template <class T>
T dictFromBase64(const QJsonValue& value){
    auto const encoded = value.toString().toLatin1();
    QByteArray ba = QByteArray::fromBase64(encoded);
    T dict = byteArrayToDict<T>(&ba);
    return dict;
}
}
#endif // SERIALIZEHELPER_H
