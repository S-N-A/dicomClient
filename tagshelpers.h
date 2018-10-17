#ifndef TAGSHELPERS_H
#define TAGSHELPERS_H

#include <QMap>
#include <QDebug>
#include <QString>

#include "gdcmReader.h"
#include "gdcmGlobal.h"
#include "gdcmDicts.h"
#include "gdcmDict.h"
#include "gdcmAttribute.h"
#include "gdcmStringFilter.h"


typedef QMap<std::string, std::pair<std::string, std::string>> dicomDict;

static dicomDict TagsMap;
dicomDict getTags(const char* filename);

#endif // TAGSHELPERS_H
