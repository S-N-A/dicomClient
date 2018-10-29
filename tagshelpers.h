#ifndef TAGSHELPERS_H
#define TAGSHELPERS_H

#include <QMap>
#include <QDebug>
#include <QString>
#include <logger.h>

#include "gdcmReader.h"
#include "gdcmGlobal.h"
#include "gdcmDicts.h"
#include "gdcmDict.h"
#include "gdcmAttribute.h"
#include "gdcmStringFilter.h"
#include "gdcmWriter.h"


typedef QMap<std::string, std::pair<std::string, std::string>> dicomDict;

static dicomDict TagsMap;
dicomDict getTags(const char* filename);
bool setTag(const std::string& offset,const std::string& value, const char* filename);

#endif // TAGSHELPERS_H
