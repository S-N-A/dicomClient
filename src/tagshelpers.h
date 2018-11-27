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
dicomDict getTags(const char* filename);
bool setTag(const std::string& offset,const std::string& value, const char* filename);

#endif // TAGSHELPERS_H
