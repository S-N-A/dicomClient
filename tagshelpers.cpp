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


bool setTag(const std::string& offset, const std::string& value, const char* filename){
    gdcm::Reader reader;
    reader.SetFileName(filename);
    if (!reader.Read()){
        return false;
    }
    gdcm::File &file = reader.GetFile();
    gdcm::DataSet &ds = file.GetDataSet();

    gdcm::Tag tempTag;
    tempTag.ReadFromContinuousString(offset.c_str());
    const gdcm::Tag tag = tempTag;
    gdcm::DataElement de = ds.GetDataElement(tag);
    de.SetByteValue(value.c_str(), static_cast<uint32_t>(std::strlen(value.c_str())));
    ds.Replace(de);

    gdcm::Writer writer;
    writer.SetFile( file );
    writer.SetFileName(filename);
    if(!writer.Write()){
        return false;
    }
    return true;

}
