#ifndef CONVERTERS_H
#define CONVERTERS_H
#include <QImage>
#include "gdcmImageReader.h"
#include "gdcmScanner.h"
#include "gdcmGlobal.h"
#include "gdcmDicts.h"
#include "gdcmDict.h"
#include "gdcmAttribute.h"
#include "gdcmStringFilter.h"
#include "gdcmCSAHeader.h"
#include "gdcmPrinter.h"

/*!
 * \brief  Функция для конвертации  изображения в файле формата dicom в изображение типа QImage
 *
 *
 */
bool ConvertToFormat_RGB888(gdcm::Image const & gimage, char *buffer, QImage* &imageQt);
/*!
 * \brief PrintCSA Функция для уведомления о наличии CSA тегов. В программе не используется.
 * \param filename Путь до dicom файла
 * \return 1 - если не найдено, 0 - если найдено
 */
int PrintCSA(const std::string filename);
#endif // CONVERTERS_H
