#ifndef TELEMEDOBJECT_H
#define TELEMEDOBJECT_H

#include <QImage>
#include <QMap>
#include <QTextCodec>
#include <QMessageBox>
#include "tagshelpers.h"
#include <QString>
#include <QException>
#include <QJsonObject>
#include <QJsonDocument>
#include "serializehelper.h"


using addInfoMap = QMap<QString, QString>;

/*!
 * \brief Класс исключения при построении объекта информации
 * \author Илья Трефилов
 * \date 01.12.2018
 *
 * Данный класс предназначен для сообщения о нештатных ситуациях при обработке объекта информации
 */
class TeleMedObjException : public QException{
public:
    /*!
     * \brief TeleMedObjException
     * \param errorString Сообщение об ошибке
     *
     * Конструктор класса исключения
     */
    TeleMedObjException(const char* errorString) : m_errorString(errorString){}
    /*!
     * \brief raise
     *
     * Функция для вызова исключения в программе
     */
    virtual void raise() const{throw *this;}
    /*!
     * \brief clone
     * \return Объект исключения
     *
     * Функция для выделения памяти под объект исключения
     */
    virtual TeleMedObjException *clone() const{return new TeleMedObjException(*this);}
    /*!
     * \brief what
     * \return Сообщение об ошибке
     *
     * Функция для получения сообщения об ошибке при исключении в программе
     */
    virtual const char* what() const noexcept{return m_errorString;}
private:
    /*!
     * \brief m_errorString
     *
     * Строка с сообщением об ошибке
     */
    const char* m_errorString;
};

/*!
 * \brief Класс объекта информации в телемедицинском сеансе
 * \author Илья Трефилов
 * \date 01.12.2018
 *
 * Данный класс предназначен для построения объекта информации для передачи\получения в телемедицинском сеансе
 */
class TeleMedObject
{

public:
    /*!
     * \brief TeleMedObject
     *
     * Конструктор по умолчанию
     */
    TeleMedObject(){}
    /*!
     * \brief TeleMedObject
     * \param img Изображение
     * \param dict Словарь с данными из исследования
     * \param map Словарь с дополнительными данными о запросе\ответе
     *
     * Конструктор выбрасывает исключение при невалидных входных данных (пустые данные)
     */
    TeleMedObject(QImage img, dicomDict dict, addInfoMap map);
    /*!
     * \brief TeleMedObject
     * \param doc Информация в виде json
     *
     * Конструктор для построения объекта из типа json
     * В данном виде данные передаются по сети
     */
    TeleMedObject(const QJsonDocument& doc);
    /*!
     * \brief getResponser
     * \return Строка идентифицирующая отвечающую сторону
     */
    QString getResponser() const;
    /*!
     * \brief toJson
     * \return Информация об объекте в виде json
     *
     * Функция строит объект информации в виде документа json
     */
    QJsonDocument toJson();
    /*!
     * \brief getImage
     * \return Изображение
     *
     * Получение изображения из объекта
     */
    QImage getImage() const;
    /*!
     * \brief getDicomDict
     * \return Словарь с информацией об исследовании
     *
     * Функция возвращает словарь с информацией об исследовании
     */
    dicomDict getDicomDict() const;
    /*!
     * \brief getInfoMap
     * \return Словарь с информацией о запросе\ответе
     *
     * Функция возвращает словарь с информацией о запросе\ответе
     */
    addInfoMap getInfoMap() const;
    /*!
     * \brief isEmpty
     * \return true - если объект информации пустой
     *
     * Функция проверяет, что объект информации пустой
     */
    bool isEmpty();

    ~TeleMedObject(){}
private:
    /*!
     * \brief m_img
     *
     * Изображение исследования
     */
    QImage m_img;
    /*!
     * \brief m_dicomDict
     *
     * Словарь с информацией об исследовании
     */
    dicomDict m_dicomDict;
    /*!
     * \brief m_addInfoMap
     *
     * Словарь с информацией о запросе\ответе
     */
    addInfoMap m_addInfoMap;
};

#endif // TELEMEDOBJECT_H
