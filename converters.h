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
#include <gdcmCompositeNetworkFunctions.h>

bool ConvertToFormat_RGB888(gdcm::Image const & gimage, char *buffer, QImage* &imageQt);
int PrintCSA(const std::string filename);
bool CEcho();
#endif // CONVERTERS_H
