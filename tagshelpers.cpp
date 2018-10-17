#include <tagshelpers.h>


dicomDict getTags(const char* filename){
    gdcm::Reader reader;
    reader.SetFileName(filename);
    if (!reader.Read()){
        qDebug() << "Couldn't read " << filename;
        TagsMap.clear();
        return TagsMap;
    }
    gdcm::File &file = reader.GetFile();
    gdcm::StringFilter sf;
    gdcm::DataSet &ds = file.GetDataSet();

    for (gdcm::DataSet::ConstIterator it = ds.Begin(); it!= ds.End(); ++it){
        const gdcm::DataElement& elem = *it;
        if (elem.GetVR() != gdcm::VR::SQ){
            const gdcm::Tag tag = elem.GetTag();
            auto pair = sf.ToStringPair(tag);
            TagsMap[tag.PrintAsContinuousString()] = pair;
        }
    }
    return TagsMap;
}
