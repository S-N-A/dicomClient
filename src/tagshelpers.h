#ifndef TAGSHELPERS_H
#define TAGSHELPERS_H

#include <QMap>
#include <QPair>
#include <QDebug>
#include <QString>
#include <logger.h>
#include <QPair>
#include "gdcmReader.h"
#include "gdcmGlobal.h"
#include "gdcmDicts.h"
#include "gdcmDict.h"
#include "gdcmAttribute.h"
#include "gdcmStringFilter.h"
#include "gdcmWriter.h"


//typedef QMap<QString, QPair<QString, QString> > dicomDict;
using dicomDict = QMap<QString, QPair<QString, QString> >;

static dicomDict TagsMap;
/*!
 * \brief getTags
 * \param filename Имя файла типа dcm
 * \return Словарь с данными из файла в формате dicom
 *
 * Функция для получения тегов dicom из файла типа dcm в словарь
 */
dicomDict getTags(const char* filename);
/*!
 * \brief setTag
 * \param offset Сдвиг по файлу, на котором находится искомый тег
 * \param value Значение тега для записи
 * \param filename Имя файла на файловой системе
 * \return true - если запись была успешна
 *
 * Функция для записи собственного значения в существующий тег файла dcm
 */
bool setTag(const std::string& offset,const std::string& value, const char* filename);

/*!
 * \brief getNameFromDict
 * \param dict Словарь с данными об исследовании
 * \return Имя пациента
 *
 * Функция получает имя пациента из набора данных об исследовании
 */
QString getNameFromDict(dicomDict& dict);

#endif // TAGSHELPERS_H
