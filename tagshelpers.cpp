#include <tagshelpers.h>


dicomDict getTags(const char* filename){
    gdcm::Reader reader;
    reader.SetFileName(filename); // set filename for reader
    if (!reader.Read()){ // if read was unsuccessfull
        qDebug() << "Couldn't read " << filename;
        TagsMap.clear();
        return TagsMap; // return empty map
    }
    gdcm::File &file = reader.GetFile();
    gdcm::DataSet &ds = file.GetDataSet();
    gdcm::StringFilter sf;
    sf.SetFile(reader.GetFile()); // this one is really important for correct string handling

    for (gdcm::DataSet::ConstIterator it = ds.Begin(); it!= ds.End(); ++it){
        const gdcm::DataElement& elem = *it;
        if (elem.GetVR() != gdcm::VR::SQ){
            const gdcm::Tag tag = elem.GetTag();
            auto value = ds.GetDataElement(tag);
            auto pair = sf.ToStringPair(value.GetTag());
            TagsMap[tag.PrintAsContinuousString()] = pair;
        }
    }
    return TagsMap;
}
